#pragma once

#include "OrCondition.h"

#include "../../engine/TableField.cpp"
#include "../../engine/DataType.cpp"

bool OrCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    for (BaseCondition* operand: operands) {
        if (operand->calculate(fields, row) == true) {
            return true^isNegated;
        }
    }
    return false^isNegated;
}