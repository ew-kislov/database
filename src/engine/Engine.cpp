#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Engine.h"

#include "../shared/VectorHelper.cpp"

#include "Table.cpp"
#include "TableField.cpp"
#include "DataTypeHelper.cpp"
#include "DataTypeEnum.h"
#include "DataType.cpp"
#include "Varchar.cpp"
#include "Number.cpp"
#include "TableRow.cpp"

#include "TableIO.cpp"

#include "EngineStatusEnum.h"
#include "EngineException.cpp"

#include "Config.h"

using namespace std;

/*
 * creates table with given name and fields
 * @param table - Table object containing name and fields
 * @throws EngineException
 */
void Engine::createTable(Table table) {
    int tableFD =  TableIO::getFD(table.getName(), TableIO::CREATE_WRITE_MODE);
    
    TableIO::writeFieldsNumber(tableFD, table.getFields().size());

    for (TableField* field : table.getFields()) {
        TableIO::writeTableField(tableFD, field);
    }

    TableIO::closeFD(tableFD);
}

/*
 * loads table with given name, optionally with rows
 * @param tableName - name of table
 * @param withRows - if true returns table with rows and fields, otherwise only fields
 * @throws EngineException
 * @returns Table object
 */
Table Engine::loadTable(string tableName, bool withRows) {
    int tableFD =  TableIO::getFD(tableName, TableIO::READ_MODE);
    
    int fieldsNumber = TableIO::readFieldsNumber(tableFD);

    int headerOffset = 0;
    int bytesRead = 0;

    vector<TableField*> fields;
    for (int i = 0; i < fieldsNumber; i++) {
        fields.push_back(TableIO::readTableField(tableFD, bytesRead));
        headerOffset += bytesRead;
    }

    if (!withRows) {
        return Table(tableName, fields, headerOffset);
    }

    vector<TableRow> rows;

    bool isRowFound = true;
    while (isRowFound) {
        TableRow row;
        for (int i = 0; i < fieldsNumber; i++) {
            DataType* value;

            try {
                value = TableIO::readTableValue(tableFD, fields[i]->getType());
            } catch(EngineException& e) {
                if (i == 0) {
                    isRowFound = false;
                    break;
                } else {
                    throw;
                }
            }
            
            row.addValue(value);
        }
        if (isRowFound) {
            bool deleted = TableIO::readRowDeletedFlag(tableFD);
            if (!deleted) {
                rows.push_back(row);
            }
        }
    }

    TableIO::closeFD(tableFD);

    return Table(tableName, fields, rows, headerOffset);
}


/*
 * inserts rows into table
 * @param tableName - name of table
 * @param rows - rows to be inserted
 * @throws EngineException
 */
void Engine::insertIntoTable(string tableName, vector<TableRow> rows) {
    int tableFD = TableIO::getFD(tableName, TableIO::WRITE_MODE);
    int seekResult = lseek(tableFD, 0, SEEK_END);

    Table table = Engine::loadTable(tableName);

    for (TableRow row: rows) {
        vector<DataType*> values = row.getValues();

        if (table.getFields().size() != values.size()) {
            cout << table.getFields().size() << " " << values.size() << endl;
            throw EngineException(EngineStatusEnum::WrongValuesNumber);
        }

        for (int i = 0; i < values.size(); i++) {
            if (table.getFields()[i]->getType() != values[i]->getType()) {
                throw EngineException(EngineStatusEnum::WrongValueType);
            }

            TableIO::writeTableValue(tableFD, values[i]);
        }

        TableIO::writeRowDeletedFlag(tableFD, row.isDeleted());
    }

    TableIO::closeFD(tableFD);
}


/*
 * updates table rows with given value
 * @param tableName - name of table
 * @param rows - rows to be updated
 * @param field - field to be updated
 * @param value - new value of field
 * @throws EngineException
 */
void Engine::updateValuesInTable(string tableName, vector<TableRow> rows, TableField* field, DataType* value) {
    if (field->getType() != value->getType()) {
        throw EngineException(EngineStatusEnum::FieldValueTypesDontMatch);
    }
    
    int tableFD =  TableIO::getFD(tableName, TableIO::READ_WRITE_MODE);
    int fieldsNumber = TableIO::readFieldsNumber(tableFD);

    int headerOffset = 0;
    int bytesRead = 0;

    vector<TableField*> fields;
    for (int i = 0; i < fieldsNumber; i++) {
        fields.push_back(TableIO::readTableField(tableFD, bytesRead));
        headerOffset += bytesRead;
    }

    int fieldIndex = VectorHelper::findInPointerVector(fields, field);
    if (fieldIndex == -1) {
        throw EngineException(EngineStatusEnum::NoSuchField);
    }

    bool isRowFound = true;
    while (isRowFound) {
        TableRow row;
        int rowSize = 0;
        int bytesRead = 0;

        for (int i = 0; i < fieldsNumber; i++) {
            bytesRead = 0;
            DataType* value;

            try {
                value = TableIO::readTableValue(tableFD, fields[i]->getType(), bytesRead);
                rowSize += bytesRead;
            } catch(EngineException& e) {
                if (i == 0) {
                    isRowFound = false;
                    break;
                } else {
                    throw;
                }
            }
            
            row.addValue(value);
        }
        if (isRowFound) {
            bytesRead = 0;
            bool deleted = TableIO::readRowDeletedFlag(tableFD, bytesRead);
            rowSize += bytesRead;

            if (VectorHelper::findInVector(rows, row) != -1) {
                row.setValue(fieldIndex, value);

                TableIO::seek(tableFD, TableIO::CURRENT_WHENCE, -rowSize);

                vector<DataType*> values = row.getValues();
                for (int i = 0; i < values.size(); i++) {
                    TableIO::writeTableValue(tableFD, values[i]);
                }
                TableIO::writeRowDeletedFlag(tableFD, row.isDeleted());
            }
        }
    }

    TableIO::closeFD(tableFD);
}

/*
 * deletes given rows from table
 * @param tableName - name of table
 * @param rows - rows to be deleted
 * @throws EngineException
 */
void Engine::deleteFromTable(string tableName, vector<TableRow> rows) {
    int tableFD =  TableIO::getFD(tableName, TableIO::READ_WRITE_MODE);
    
    int fieldsNumber = TableIO::readFieldsNumber(tableFD);

    int headerOffset = 0;
    int bytesRead = 0;

    vector<TableField*> fields;
    for (int i = 0; i < fieldsNumber; i++) {
        fields.push_back(TableIO::readTableField(tableFD, bytesRead));
        headerOffset += bytesRead;
    }

    bool isRowFound = true;
    while (isRowFound) {
        TableRow row;
        for (int i = 0; i < fieldsNumber; i++) {
            DataType* value;

            try {
                value = TableIO::readTableValue(tableFD, fields[i]->getType());
            } catch(EngineException& e) {
                if (i == 0) {
                    isRowFound = false;
                    break;
                } else {
                    throw;
                }
            }
            
            row.addValue(value);
        }
        if (isRowFound) {
            bool deleted = TableIO::readRowDeletedFlag(tableFD);
            if (!deleted && VectorHelper::findInVector(rows, row) != -1) {
                TableIO::seek(tableFD, TableIO::CURRENT_WHENCE, -sizeof(bool));
                TableIO::writeRowDeletedFlag(tableFD, true);
            }
        }
    }

    TableIO::closeFD(tableFD);
}