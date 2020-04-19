#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "Table.h"
#include "TableField.h"
#include "TableRow.h"

using namespace std;

namespace Engine {
    Table loadTable(string tableName, bool withRows = false);
    
    void createTable(Table table);
    void insertIntoTable(string tableName, vector<TableRow> rows);
    void deleteFromTable(string table, vector<TableRow> rows);
}

#endif