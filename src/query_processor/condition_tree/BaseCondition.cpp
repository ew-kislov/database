#pragma once

#include "BaseCondition.h"

bool BaseCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    throw "BaseCondition: calculate() not implemented";
}