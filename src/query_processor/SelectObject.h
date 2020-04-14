#ifndef SELECT_OBJECT_H
#define SELECT_OBJECT_H

#include "QueryObject.h"
#include "condition_tree/BaseCondition.h"

using namespace std;

class SelectObject: public QueryObject {
    protected:
        vector<string> fields;
    public:
        BaseCondition* treeRoot;
    
        SelectObject(string table, vector<string> fields);
    
        vector<string> getFields();
};

#endif
