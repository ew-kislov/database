#pragma once

#include "OrCondition.h"

bool OrCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    for (BaseCondition* operand: operands) {
        if (operand->calculate(fields, row) == true) {
            return true^isNegated;
        }
    }
    return false^isNegated;
}