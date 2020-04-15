#include "LikeCondition.h"

LikeCondition::LikeCondition(BaseOperand* operand1, BaseOperand* operand2) : BinaryCondition(operand1, operand2) {}

bool LikeCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    if (
        operand1->getType() != OperandTypeEnum::TABLE_FIELD ||
        operand2->getType() != OperandTypeEnum::STRING)
    ) {
        cout << "Wrong arguments" << endl;
        // TODO: throw exception
    }
    
    TableFieldOperand* fieldOperand = dynamic_cast<TableFieldOperand*>(operand1);
    
    field = new TableField(fieldOperand->getValue(), DataTypeEnum::STRING);
    
    
}
