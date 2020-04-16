#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "Table.h"
#include "TableField.h"

using namespace std;

namespace Engine {
    Table loadTable(string tableName, bool withRows = false);
    
    void createTable(string tableName, vector<TableField*> fields);
}

#endif