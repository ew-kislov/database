#pragma once

#include "SelectObject.h"

SelectObject::SelectObject(string table, vector<string> fields, OrCondition* conditionTree): QueryObject(QueryTypeEnum::Select, table) {
    this->fields = fields;
    this->conditionTree = conditionTree;
}

vector<string> SelectObject::getFields() {
    return this->fields;
}

OrCondition* SelectObject::getConditionTree() {
    return this->conditionTree;
}

string SelectObject::toString() {
    string selectString;
    
    selectString += "SelectObject {\n";
    selectString += "\ttable: " + getTable() + ",\n";
    selectString += "\tconditionTree:\n" + conditionTree->toString(3);
    selectString += "}\n";
    
    return selectString;
}
