#pragma once

#include "DeleteObject.h"

DeleteObject::DeleteObject(string table, OrCondition* conditionTree): QueryObject(QueryTypeEnum::Delete, table) {
    this->conditionTree = conditionTree;
}

string DeleteObject::toString() {
    string deleteString;
    
    deleteString += "DeleteObject {\n";
    deleteString += "\tconditionTree:\n" + conditionTree->toString(4) + "\n";
    deleteString += "}";
    
    return deleteString;
}
