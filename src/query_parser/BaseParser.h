#ifndef BASE_PARSER_H
#define BASE_PARSER_H

#include <string>
#include <iostream>

#include "QueryObject.h"

using namespace std;

class BaseParser {
    public:
        virtual QueryObject parse(string query) = 0;
};

#endif