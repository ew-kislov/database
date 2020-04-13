#pragma once

#include "BaseOperand.h"

OperandTypeEnum BaseOperand::getType() {
    return type;
}

BaseOperand::BaseOperand() {

}

BaseOperand::BaseOperand(OperandTypeEnum type) {
    this->type = type;
}