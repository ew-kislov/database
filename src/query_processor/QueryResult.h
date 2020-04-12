#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <string>
#include <vector>

#include "QueryStatusEnum.h"

using namespace std;

class QueryResult {
    protected:
        string table;
        QueryStatusEnum status;
        int executionTime;
    public:
        QueryResult(string table, QueryStatusEnum status, int executionTime);
};

#endif