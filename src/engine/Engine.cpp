#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "fcntl.h"
#include "unistd.h"

#include "Engine.h"

#include "Table.cpp"
#include "TableField.cpp"
#include "DataTypeFactory.cpp"
#include "DataTypeEnum.h"
#include "DataType.cpp"
#include "Varchar.cpp"
#include "Number.cpp"

#include "EngineException.cpp"

#include "Config.h"

using namespace std;

/*
 * Loads table from storage directory
 * @param tableName - name of table
 * @throws std::ios_base::failure
 * @returns table fields and values in Table object
 */
// Table Engine::loadTable(string tableName, bool withRows) {
//     // Open file containing table

//     ifstream tableFile;
//     tableFile.open(Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION);

//     // Read fields number

//     int fieldsNumber;
//     tableFile >> fieldsNumber;

//     // Read table feilds

//     string fieldName;
//     int fieldTypeOrdinal;

//     vector<TableField> fields;

//     for (int i = 0; i < fieldsNumber; i++) {
//         tableFile >> fieldName >> fieldTypeOrdinal;
//         fields.push_back(TableField(fieldName, static_cast<DataTypeEnum>(fieldTypeOrdinal)));
//     }

//     // check if rows are demanded

//     if (!withRows) {
//         return Table(tableName, fields);
//     }

//     // Read table rows

//     vector<vector<DataType*> > rows;
//     vector<DataType*> row;

//     string rowString;
//     string valueString;
        
//     while (getline(tableFile, rowString)) {
//         row.clear();
//         for (int i = 0; i < fieldsNumber; i++) {
//             tableFile >> valueString;
//             row.push_back(DataTypeFactory::create(valueString, fields[i].getType()));
//         }
//         rows.push_back(row);
//     }

//     return Table(tableName, fields, rows);
// }

void Engine::createTable(string tableName, vector<TableField*> fields) {
    int tableFd = open((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(), O_WRONLY | O_CREAT, 0666);
    
    if (tableFd == -1) {
        throw "Error while creating file";
        // TODO: determine type and throw custom exception
    }
    
    int fieldNumber = fields.size();
    write(tableFd, &fieldNumber, sizeof(fieldNumber));

    for (TableField* field : fields) {
        int fieldNameSize = field->getName().length();
        const char* fieldName = field->getName().c_str();
        int fieldType = field->getType();

        write(tableFd, &fieldNameSize, sizeof(int));
        write(tableFd, fieldName, fieldNameSize * sizeof(char));
        write(tableFd, &fieldType, sizeof(int));
    }

    close(tableFd);
}

Table Engine::loadTable2(string tableName, bool withRows) {
    int tableFd = open((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(), O_RDONLY, 0666);

    if (tableFd == -1) {
        throw "Error while reading file";
        // TODO: determine type and throw custom exception
    }
    
    int fieldNumber;
    read(tableFd, &fieldNumber, sizeof(fieldNumber));

    int fieldNameSize;
    char fieldName[Config::MAX_FIELD_NAME_SIZE];
    int fieldType;

    vector<TableField*> fields;

    for (int i = 0; i < fieldNumber; i++) {
        read(tableFd, &fieldNameSize, sizeof(int));

        read(tableFd, &fieldName, fieldNameSize * sizeof(char));
        fieldName[fieldNameSize] = '\0';

        read(tableFd, &fieldType, sizeof(int));

        fields.push_back(new TableField(string(fieldName), static_cast<DataTypeEnum>(fieldType)));
    }

    vector<vector<DataType*> > rows;

    bool isFieldFound = true;
    while (isFieldFound) {
        vector<DataType*> row;
        for (int i = 0; i < fieldNumber; i++) {
            DataType* value;
            int bytesRead;

            if (fields[i]->getType() == DataTypeEnum::NUMBER) {
                long double numberValue;
                bytesRead = read(tableFd, &numberValue, sizeof(long double));

                if (bytesRead <= 0) {
                    if (i == 0) {
                        isFieldFound = 0;
                        break;
                    } else {
                        throw "Table structure corrupted";
                        // TODO: throw engine exception
                    }
                }

                value = new Number(numberValue);
            } else if (fields[i]->getType() == DataTypeEnum::VARCHAR) {
                char varcharValue[50];
                int length;

                bytesRead = read(tableFd, &length, sizeof(int));
                bytesRead = read(tableFd, varcharValue, length * sizeof(char));

                if (bytesRead <= 0) {
                    if (i == 0) {
                        isFieldFound = 0;
                        break;
                    } else {
                        throw "Table structure corrupted";
                        // TODO: throw engine exception
                    }
                }

                varcharValue[length] = '\0';
                value = new Varchar(varcharValue, false);
            }

            row.push_back(value);
        }
        if (isFieldFound) {
            rows.push_back(row);
        }
    }

    close(tableFd);

    cout << rows.size() << endl;

    return Table(tableName, fields, rows);
}

void Engine::insertIntoTable(string tableName, vector<vector<DataType*> > rows) {
    int tableFd = open((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(), O_WRONLY | O_APPEND, 0666);
    int seekResult = lseek(tableFd, 0, SEEK_END);

    Table table = Engine::loadTable2(tableName);

    for (vector<DataType*> row: rows) {
        if (table.getFields().size() != row.size()) {
            // TODO: throw engine exception
            throw "Wrong values number";
        }

        for (int i = 0; i < row.size(); i++) {
            if (table.getFields()[i]->getType() != row[i]->getType()) {
                // TODO: throw engine exception
                throw "Wrong value type";
            }

            DataType* value = row[i];
            int bytesWritten;

            if (value->getType() == DataTypeEnum::NUMBER) {
                Number* number = dynamic_cast<Number*>(value);
                long double numberValue = number->getValue();

                bytesWritten = write(tableFd, &numberValue, sizeof(long double));
            } else if (value->getType() == DataTypeEnum::VARCHAR) {
                Varchar* varchar = dynamic_cast<Varchar*>(value);
                string varcharValue = varchar->getValue();
                int length = varcharValue.size();

                bytesWritten = write(tableFd, &length, sizeof(int));
                bytesWritten = write(tableFd, varcharValue.c_str(), length * sizeof(char));
            }
        }
    }

    close(tableFd);
}

int main() {
    // vector<TableField*> fields;
    // fields.push_back(new TableField("f1", DataTypeEnum::NUMBER));
    // fields.push_back(new TableField("f2", DataTypeEnum::VARCHAR));
    // fields.push_back(new TableField("f3", DataTypeEnum::NUMBER));

    // Engine::createTable("table", fields);
    Table table = Engine::loadTable2("table", true);
    cout << table << endl;

    // vector<vector<DataType*> > rows;

    // vector<DataType*> row;
    // row.push_back(new Number("1"));
    // row.push_back(new Varchar("'v1'"));
    // row.push_back(new Number("123"));

    // rows.push_back(row);

    // row.clear();
    // row.push_back(new Number("2"));
    // row.push_back(new Varchar("'v2'"));
    // row.push_back(new Number("54656.45"));

    // rows.push_back(row);

    // Engine::insertIntoTable("table", rows);
}