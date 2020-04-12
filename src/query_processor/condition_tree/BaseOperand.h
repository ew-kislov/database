#ifndef BASE_OPERAND_H
#define BASE_OPERAND_H

#include "OperandTypeEnum.h"

class BaseOperand {
    protected:
        OperandTypeEnum type;
    public:
        OperandTypeEnum getType();
};

#endif