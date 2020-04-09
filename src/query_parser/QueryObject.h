#ifndef QUERY_OBJECT_H
#define QUERY_OBJECT_H

#include <map>
#include <string>
#include <vector>

#include "QueryType.h"

using namespace std;

struct QueryObject {
    QueryType queryType;
    string table;
    vector<string> fields;
    vector<string> fieldTypes;
    vector<pair<string, string> > filter;
    map<string, string> values;

    // TODO: make getters/setters with immutable fields(except queryType/table)
    // TODO: implement operator<<
    // TODO: inheritence ?
};

#endif