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
    deleteString += "   table: " + getTable() + ",\n";
    deleteString += "   conditionTree:\n" + conditionTree->toString(3) + "\n";
    deleteString += "}\n";
    
    return deleteString;
}
