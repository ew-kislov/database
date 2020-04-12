#pragma once

#include "AndCondition.h"

bool AndCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    for (BaseCondition operand: operands) {
        if (operand.calculate(fields, row) == false) {
            return false^isNegated;
        }
    }
    return true^isNegated;
}