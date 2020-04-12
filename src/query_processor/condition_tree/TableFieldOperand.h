#ifndef TABLE_FIELD_OPERAND_H
#define TABLE_FIELD_OPERAND_H

#include <set>

#include "BaseOperand.h"

using namespace std;

class TableFieldOperand : public BaseOperand {
    protected:
        OperandTypeEnum type = OperandTypeEnum::TableField;
        string value;
    public:
        TableFieldOperand(string value);
};

#endif