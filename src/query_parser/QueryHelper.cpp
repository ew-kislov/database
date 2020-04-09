#pragma once

#include <string>
#include <vector>

#include "StringHelper.cpp"

using namespace std;

namespace QueryHelper {
    int searchKeyWordInVector(vector<string> queryVector, string keyWord) {
        for (int i = 0; i < queryVector.size(); i++) {
            if (StringHelper::getUpperString(queryVector[i]) == StringHelper::getFirstWord(keyWord)) {
                return i;
            }
        }

        return -1;
    }
}