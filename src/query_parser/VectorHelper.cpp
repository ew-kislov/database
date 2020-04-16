#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace VectorHelper {
    /*
     * Prints vector on the same line, elements divided by space
     * @param inpVector - input vector
     */
    template<class T> void print(vector<T> inpVector) {
        for (int i = 0; i < inpVector.size(); i++) {
            cout << inpVector[i] << " ";
        }
        cout << endl;
    }

    /*
     * Returns vector with elements [startIndex; endIndex] of input array
     * If end index not specified then [startIndex; inputVector.size()] is returned
     * @param inpVector - input vector
     * @param startIndex - start index of new vector
     * @param endIndex - end index of new vector
     * @returns vector with elements [startIndex; endIndex] of input array
     */
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

    template<class T> void removeByIndex(vector<T> &inpVector, int index) {
        inpVector.erase(inpVector.begin() + index);
    }
}
