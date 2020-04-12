#ifndef QUERY_OBJECT_H
#define QUERY_OBJECT_H

#include <map>
#include <string>
#include <vector>

#include "QueryTypeEnum.h"

using namespace std;

class QueryObject {
    protected:
        QueryTypeEnum type;
        string table;
    public:
        QueryTypeEnum getType();
        string getTable();
};

#endif