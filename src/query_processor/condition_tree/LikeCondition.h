#ifndef LIKE_CONDITION_H
#define LIKE_CONDITION_H

#include "BinaryCondition.h"

using namespace std;

class LikeCondition : public BinaryCondition {
    public:
        LikeCondition(BaseOperand* operand1, BaseOperand* operand2);

        bool calculate(vector<TableField> fields, vector<DataType*> row);
};

#endif
