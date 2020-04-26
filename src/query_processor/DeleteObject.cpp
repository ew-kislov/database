#pragma once

#include "DeleteObject.h"

DeleteObject::DeleteObject(string table, OrCondition* conditionTree): QueryObject(QueryTypeEnum::Delete, table) {
    this->conditionTree = conditionTree;
}

OrCondition* DeleteObject::getConditionTree() {
    return this->conditionTree;
}

string DeleteObject::toString() {
    string deleteString;
    
    deleteString += "DeleteObject {\n";
    deleteString += "\ttable: " + getTable() + ",\n";
    deleteString += "\tconditionTree:\n" + conditionTree->toString(3) + "\n";
    deleteString += "}\n";
    
    return deleteString;
}
