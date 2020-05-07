#ifndef ENGINE_STATUS_STRINGS_H
#define ENGINE_STATUS_STRINGS_H

#include <string>

using namespace std;

const string engineStatusString[11] = {
    "",
    "Table already exists",
    "You don't have permission for this operation",
    "Table doesn't exist",
    "Table structure corrupted",
    "Wrong number of values given",
    "Wrong value type",
    "Invalid value given",
    "No such field",
    "Field and value fields don't match",
    "Internal error"
};

#endif