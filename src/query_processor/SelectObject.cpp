#include "SelectObject.h"

SelectObject::SelectObject(string table, vector<string> fields): QueryObject(QueryTypeEnum::Select, table) {
    this->fields = fields;
}

vector<string> SelectObject::getFields() {
    return this->fields;
}

string SelectObject::toString() {
    return "";
}