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

string AndCondition::toString(int nestLevel) {
    string message;
    
    if (this->NegatableCondition::isNegated)
        message += "NOT ";
    
    if (operands.size() > 1) {
        message += "AND Condition (\n";
           
        for (BaseCondition* it: operands) {
            message += string(nestLevel,'\t');
            message += it->toString(nestLevel + 1);
        }
        
        message += string(nestLevel - 1,'\t');
        message += ")";
        message += "\n";
        
    } else {
        message += operands[0]->toString();
    }
    
    return message;
}
