#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "../engine/Table.h"

#include "QueryObject.h"
// #include "QueryResult.h"

namespace QueryProcessor {
    string executeQuery(QueryObject* queryObject);
    string executeSelect(QueryObject* queryObject);
    string executeInsert(QueryObject* queryObject);
    string executeUpdate(QueryObject* queryObject);
    string executeDelete(QueryObject* queryObject);
    string executeCreate(QueryObject* queryObject);
    string executeDrop(QueryObject* queryObject);
}

#endif