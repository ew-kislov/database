#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Engine.h"

#include "Table.cpp"
#include "TableField.cpp"
#include "DataTypeFactory.cpp"
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

    vector<TableField*> fields;
    for (int i = 0; i < fieldsNumber; i++) {
        fields.push_back(TableIO::readTableField(tableFD));
    }

    if (!withRows) {
        return Table(tableName, fields);
    }

    vector<TableRow> rows;

    bool isFieldFound = true;
    while (isFieldFound) {
        TableRow row;
        for (int i = 0; i < fieldsNumber; i++) {
            DataType* value;

            try {
                value = TableIO::readTableValue(tableFD, fields[i]->getType());
            } catch(EngineException& e) {
                if (i == 0) {
                    isFieldFound = false;
                    break;
                } else {
                    throw;
                }
            }
            
            row.addValue(value);
        }
        if (isFieldFound) {
            rows.push_back(row);
        }
    }

    TableIO::closeFD(tableFD);

    return Table(tableName, fields, rows);
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

            DataType* value = values[i];
            TableIO::writeTableValue(tableFD, value);
        }
    }

    TableIO::closeFD(tableFD);
}

int main() {
    // Engine::createTable(table);

    TableRow row;
    row.addValue(new Number(1));
    row.addValue(new Varchar("'wdwwww'"));
    row.addValue(new Varchar("'qaaaa'"));

    vector<TableRow> rows;
    rows.push_back(row);

    TableRow row2;
    row2.addValue(new Number(2));
    row2.addValue(new Varchar("'wdwwww'"));
    row2.addValue(new Varchar("'qaaaa'"));

    rows.push_back(row2);

    // Engine::insertIntoTable("some_table", rows);

    Table table2 = Engine::loadTable("some_table", true);
    cout << table2 << endl;
}