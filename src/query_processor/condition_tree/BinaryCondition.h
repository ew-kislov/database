#ifndef BINARY_CONDITION_H
#define BINARY_CONDITION_H

#include "BaseCondition.h"

#include "BaseOperand.h"

using namespace std;

class BinaryCondition : public BaseCondition {
    protected:
        BaseOperand operand1;
        BaseOperand operand2;
    public:
        virtual bool calculate(vector<TableField> fields, vector<DataType*> row);
};

#endif