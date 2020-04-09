#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace VectorHelper {
    template<class T> void print(vector<T> inpVector) {
        for (int i = 0; i < inpVector.size(); i++) {
            cout << inpVector[i] << " ";
        }
        cout << endl;
    }

    template<class T> vector<T> slice(vector<T> inpVector, int startIndex, int endIndex = -1) {
        if (endIndex == -1) {
            endIndex = inpVector.size() - 1;
        }

        if (
            startIndex < 0 || endIndex < 0 ||
            startIndex >= inpVector.size() || endIndex >= inpVector.size() ||
            startIndex > endIndex
        ) {
            throw logic_error("Wrong indexes");
        }

        return vector<T>(inpVector.begin() + startIndex, inpVector.begin() + endIndex + 1);
    }
}