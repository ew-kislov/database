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

#include "EngineException.cpp"

#include "Config.h"

using namespace std;

/*
 * Loads table from storage directory
 * @param tableName - name of table
 * @throws std::ios_base::failure
 * @returns table fields and values in Table object
 */
Table Engine::loadTable(string tableName, bool withRows) {
    // Open file containing table

    ifstream tableFile;
    tableFile.open(Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION);

    // Read fields number

    int fieldsNumber;
    tableFile >> fieldsNumber;

    // Read table feilds

    string fieldName;
    int fieldTypeOrdinal;

    vector<TableField> fields;

    for (int i = 0; i < fieldsNumber; i++) {
        tableFile >> fieldName >> fieldTypeOrdinal;
        fields.push_back(TableField(fieldName, static_cast<DataTypeEnum>(fieldTypeOrdinal)));
    }

    // check if rows are demanded

    if (!withRows) {
        return Table(tableName, fields);
    }

    // Read table rows

    vector<vector<DataType*> > rows;
    vector<DataType*> row;

    string rowString;
    string valueString;
        
    while (getline(tableFile, rowString)) {
        row.clear();
        for (int i = 0; i < fieldsNumber; i++) {
            tableFile >> valueString;
            row.push_back(DataTypeFactory::create(valueString, fields[i].getType()));
        }
        rows.push_back(row);
    }

    return Table(tableName, fields, rows);
}

int main() {
    Engine::loadTable("cats");
}