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

#include "EngineStatusEnum.h"
#include "EngineException.cpp"

#include "Config.h"

using namespace std;

void Engine::createTable(string tableName, vector<TableField*> fields) {
    int tableFd = open((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(), O_WRONLY | O_CREAT, 0666);
    
    if (tableFd == -1) {
        throw EngineException(EngineStatusEnum::TableAlreadyExists);
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

Table Engine::loadTable(string tableName, bool withRows) {
    int tableFd = open((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(), O_RDONLY, 0666);

    if (tableFd == -1) {
        throw EngineException(EngineStatusEnum::TableDoesNotExist);
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
                        throw EngineException(EngineStatusEnum::TableStructureCorrupted);
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
                        throw EngineException(EngineStatusEnum::TableStructureCorrupted);
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

    Table table = Engine::loadTable(tableName);

    for (vector<DataType*> row: rows) {
        if (table.getFields().size() != row.size()) {
            throw EngineException(EngineStatusEnum::WrongValuesNumber);
        }

        for (int i = 0; i < row.size(); i++) {
            if (table.getFields()[i]->getType() != row[i]->getType()) {
                throw EngineException(EngineStatusEnum::WrongValueType);
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

// int main() {
//     Table table = Engine::loadTable("table", true);
//     cout << table << endl;
// }