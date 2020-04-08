#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <string>
#include <iostream>
#include <algorithm>

#include "BaseParser.h"
#include "QueryObject.h"

using namespace std;

class QueryParser: public BaseParser {
    public:
        QueryObject parse(string query);
};

#endif