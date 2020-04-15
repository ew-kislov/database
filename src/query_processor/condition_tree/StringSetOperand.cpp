#pragma once

#include "StringSetOperand.h"

#include "../../engine/EngineException.cpp"

StringSetOperand::StringSetOperand(set<string> value) : BaseOperand(OperandTypeEnum::STRING_SET) {
    this->value = value;
}

bool StringSetOperand::contains(string inpString) {
    for (set<string>::iterator it = value.begin(); it != value.end(); ++it) {
        if (!inpString.compare(*it)) {
            return true;
        }
    }
    return false;
}
