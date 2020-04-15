#pragma once

#include "InCondition.h"

#include "TableFieldOperand.cpp"
#include "NumberSetOperand.cpp"
#include "../VectorHelper2.cpp"

#include <iostream>

using namespace std;

InCondition::InCondition(BaseOperand* operand1, BaseOperand* operand2) : BinaryCondition(operand1, operand2) {
    
}

bool InCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    if (
        operand1->getType() != OperandTypeEnum::TABLE_FIELD ||
        !(operand2->getType() == OperandTypeEnum::NUMBER_SET || operand2->getType() == OperandTypeEnum::STRING_SET)
    ) {
        cout << "Wrong arguments" << endl;
        // TODO: throw exception
    }

    TableFieldOperand* fieldOperand = dynamic_cast<TableFieldOperand*>(operand1);

    TableField* field;
    if (operand2->getType() == OperandTypeEnum::NUMBER_SET) {
        field = new TableField(fieldOperand->getValue(), DataTypeEnum::NUMBER);
    } else {
        field = new TableField(fieldOperand->getValue(), DataTypeEnum::VARCHAR);
    }

    int fieldIndex = VectorHelper2::findInVector(fields, *field);
    if (fieldIndex == -1) {
        cout << "Couldn't find field with this type";
        // TODO: throw exception
    }

    if (operand2->getType() == OperandTypeEnum::NUMBER_SET) {
        NumberSetOperand* setOperand = dynamic_cast<NumberSetOperand*>(operand2);
        Number* numberOperand = dynamic_cast<Number*>(row[fieldIndex]);
        return setOperand->contains(*numberOperand);
    } else {
        // TODO
    }
}
