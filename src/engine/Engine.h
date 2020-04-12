#ifndef ENGINE_H
#define ENGINE_H

#include "Table.h"

namespace Engine {
    Table loadTable(string tableName, bool withRows = false);
}

#endif