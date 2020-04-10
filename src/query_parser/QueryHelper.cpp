#pragma once

#include <string>
#include <vector>
#include <stack>

#include "StringHelper.cpp"

using namespace std;

namespace QueryHelper {
    int searchKeyWordInVector(vector<string> queryTokens, string keyWord) {
        for (int i = 0; i < queryTokens.size(); i++) {
            if (StringHelper::getUpperString(queryTokens[i]) == StringHelper::getUpperString(keyWord)) {
                return i;
            }
        }

        return -1;
    }

    bool isTokenNested(vector<string> queryTokens, int tokenIndex) {
        stack<string> closures;

        for (int i = 0; i <= tokenIndex; i++) {
            if (queryTokens[i] == "(") {
                closures.push("(");
            } else if (queryTokens[i] == ")" && closures.empty()) {
                // TODO: throw QueryParserException("Wrong braces placement");
                cout << "Wrong braces placement" << endl;
            } else if (queryTokens[i] == ")" && !closures.empty()) {
                closures.pop();
            }
        }

        return !closures.empty();
    }
}