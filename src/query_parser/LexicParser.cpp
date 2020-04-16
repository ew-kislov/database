#pragma once

#include <string>
#include <sstream>

#include "QueryException.h"

using namespace std;

namespace LexicParser {
    string parseStringLexem(string stringLexem) {
        if (
            stringLexem[0] != '\'' ||
            stringLexem.find('\'', 1) != stringLexem.size() - 1 ||
            stringLexem.size() < 3
        ) {
            throw QueryException("Wrong string operand");
        }

        return stringLexem.substr(1, stringLexem.size() - 2);
    }

    /*
     * Splits string into set of strings by char delimeter
     * @param stringLexem - input string
     * @param delimeter - char delimeneter
     * @returns set of elements splitted by delimeter
     */
    set<string> splitToStringSet(string stringLexem, char delimeter) {
        set<string> outpSet;
        istringstream stringStream(stringLexem);
        string token;
        
        while (getline(stringStream, token, delimeter)) {
            outpSet.insert(LexicParser::parseStringLexem(token));
        }
        
        return outpSet;
    }

    /*
     * Splits string into set of long double by char delimeter
     * @param stringLexem - input string
     * @param delimeter - char delimeneter
     * @returns set of elements splitted by delimeter
     */
    set<long double> splitToNumberSet(string stringLexem, char delimeter) {
        set<long double> outpSet;
        istringstream stringStream(stringLexem);
        string token;
        
        while (getline(stringStream, token, delimeter)) {
            outpSet.insert(stold(token));
        }
        
        return outpSet;
    }
}
