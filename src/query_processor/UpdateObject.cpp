#pragma once

#include "UpdateObject.h"

UpdateObject::UpdateObject(string table, TableField* field, DataType* value, BaseCondition* conditionTree)
    : QueryObject(QueryTypeEnum::Update, table) {
        this->table = table;
        this->field = field;
        this->value = value;
        this->conditionTree = conditionTree;
}

TableField* UpdateObject::getField() {
    return field;
}

DataType* UpdateObject::getValue() {
    return value;
}

BaseCondition* UpdateObject::getConditionTree() {
    return conditionTree;
}

string UpdateObject::toString() {
    string updateString;

    updateString += "UpdateObject {\n";
    updateString += "\tfield: " + field->toString() + "\n";
    updateString += "\tvalue: " + value->toString() + "\n";
    updateString += "\tconditionTree:\n" + conditionTree->toString(5) + "\n";
    updateString += "}";

    return updateString;
}
