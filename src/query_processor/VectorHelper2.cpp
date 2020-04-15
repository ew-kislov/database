#pragma once

#include <vector>

using namespace std;

namespace VectorHelper2 {
    template < typename T> int findInVector(const vector<T>  &inpVector, const T &element) {
        auto it = std::find(inpVector.begin(), inpVector.end(), element);
    
        if (it != inpVector.end()) {
            return distance(inpVector.begin(), it);
        }
        else {
            return -1;
        }
    }
}