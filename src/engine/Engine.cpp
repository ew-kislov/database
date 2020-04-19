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

void Engine::createTable(Table table) {
    int tableFD =  TableIO::getFD(table.getName(), TableIO::CREATE_WRITE_MODE);
    
    TableIO::writeFieldsNumber(tableFD, table.getFields().size());

    for (TableField* field : table.getFields()) {
        TableIO::writeTableField(tableFD, field);
    }

    TableIO::closeFD(tableFD);
}

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

void Engine::insertIntoTable(string tableName, vector<TableRow> rows) {
    int tableFD = TableIO::getFD(tableName, TableIO::WRITE_MODE);
    int seekResult = lseek(tableFD, 0, SEEK_END);

    Table table = Engine::loadTable(tableName);

    for (TableRow row: rows) {
        vector<DataType*> values = row.getValues();

        if (table.getFields().size() != values.size()) {
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

int main() {
    // vector<TableField*> fields;
    // fields.push_back(new TableField("f1", DataTypeEnum::NUMBER));
    // fields.push_back(new TableField("f2", DataTypeEnum::VARCHAR));
    // fields.push_back(new TableField("f3", DataTypeEnum::VARCHAR));

    // Table table("some_table", fields);

    // Engine::createTable(table);

    TableRow row;
    row.addValue(new Number(2));
    row.addValue(new Varchar("'qweffgfgrt'"));
    row.addValue(new Varchar("'ddffergwrgwrff'"));

    vector<TableRow> rows;
    rows.push_back(row);

    // TableRow row2;
    // row2.addValue(new Number(4));
    // row2.addValue(new Varchar("'aaaaaa'"));
    // row2.addValue(new Varchar("'bbbbb'"));

    // rows.push_back(row2);

    // Engine::insertIntoTable("some_table", rows);

    // Engine::deleteFromTable("some_table", rows);

    Table table2 = Engine::loadTable("some_table", true);
    cout << table2 << endl;
}