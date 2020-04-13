#pragma once

#include "NumberSetOperand.h"

NumberSetOperand::NumberSetOperand(set<long double> value) : BaseOperand(OperandTypeEnum::NUMBER_SET) {
    this->value = value;
}

bool NumberSetOperand::contains(Number number) {
    set<long double>::iterator it = value.begin();
    while (it != value.end()) {
        if (number == *it) {
            return true;
        }
        it++;
    }
    return false;
}