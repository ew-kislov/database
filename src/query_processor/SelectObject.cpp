#include "SelectObject.h"

SelectObject::SelectObject(string table, vector<string> fields): QueryObject(QueryTypeEnum::Select, table) {
    this->fields = fields;
//    this->treeRoot = new OrCondition;
}


vector<string> SelectObject::getFields() {
    return this->fields;
}
