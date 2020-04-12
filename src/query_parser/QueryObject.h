#ifndef QUERY_OBJECT_H
#define QUERY_OBJECT_H

#include <map>
#include <string>
#include <vector>

#include "QueryTypeEnum.h"

using namespace std;

struct QueryObject {
    QueryTypeEnum type;
    string table;
    vector<string> fields;
    vector<string> fieldTypes;
    vector<pair<string, string> > filter;
    map<string, string> values;
};

#endif