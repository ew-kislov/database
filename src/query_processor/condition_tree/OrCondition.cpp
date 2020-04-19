#pragma once

#include "OrCondition.h"

#include "../../engine/TableField.cpp"
#include "../../engine/DataType.cpp"

#include <string>

bool OrCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    for (BaseCondition* operand: operands) {
        if (operand->calculate(fields, row) == true) {
            return true^isNegated;
        }
    }
    return false^isNegated;
}

string OrCondition::toString() {
    string message;
    
    if (this->NegatableCondition::isNegated)
        message += "NOT ";
    
    message += "OrCondition (\n";
    
    for (BaseCondition* it: operands) {
        message += it->toString();
    }
    
    message += ") /or/\n";
    
    return message;
}
