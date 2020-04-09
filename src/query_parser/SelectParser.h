#ifndef SELECT_PARSER_H
#define SELECT_PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

#include "QueryObject.h"

using namespace std;

class SelectParser {
    public:
        static QueryObject parse(string query);
};

#endif