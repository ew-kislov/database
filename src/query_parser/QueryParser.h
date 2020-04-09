#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <string>
#include <iostream>
#include <algorithm>

#include "QueryObject.h"

using namespace std;

class QueryParser {
    public:
        static QueryObject parse(string query);
};

#endif