#pragma once

#include "InCondition.h"

#include <iostream>

using namespace std;

bool InCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    if (operand1.getType() != OperandTypeEnum::TableField ||
        operand2.getType() != OperandTypeEnum::NumberSet ||
        operand2.getType() != OperandTypeEnum::StringSet
    ) {
        cout << "Wrong argiments";
        // TODO: throw exception
    }

    
}