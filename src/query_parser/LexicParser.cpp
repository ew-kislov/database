#pragma once

#include <string>

#include "QueryException.h"

using namespace std;

namespace LexicParser {
    string parseStringLexem(string stringLexem) {
        if (stringLexem[0] != '\'' || stringLexem[stringLexem.size() - 1] != '\'') {
            throw QueryException("Wrong string operand");
        }

        return stringLexem.substr(1, stringLexem.size() - 2);
    }
}