#pragma once

#include "AndCondition.h"

#include <string>


bool AndCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    for (BaseCondition* operand: operands) {
        if (operand->calculate(fields, row) == false) {
            return false^isNegated;
        }
    }
    return true^isNegated;
}

string AndCondition::toString() {
    string message = "\t";
    
    if (this->NegatableCondition::isNegated)
        message += "NOT ";
    
    message += "AndCondition:\n";
    
    for (BaseCondition* it: operands) {
        message += it->toString();
    }
    
    message += "/and/\n";
    
    return message;
}
