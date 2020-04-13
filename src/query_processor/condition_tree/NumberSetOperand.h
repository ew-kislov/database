#ifndef NUMBER_SET_OPERAND_H
#define NUMBER_SET_OPERAND_H

#include <set>

#include "BaseOperand.h"

using namespace std;

class NumberSetOperand : public BaseOperand {
    protected:
        OperandTypeEnum type;
        set<long double> value;
    public:
        NumberSetOperand(set<long double> value);

        bool contains(Number number);
};

#endif