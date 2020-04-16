#include "RelationCondition.h"

#include <string>

RelationCondition::RelationCondition(BaseOperand* operand1, BaseOperand* operand2, string relationType) : BinaryCondition(operand1, operand2) {
    if (!relationType.compare("=")) {
        this->relationType = RelationTypeEnum::EQ;
    } else if (!relationType.compare("!=")) {
        this->relationType = RelationTypeEnum::NEQ;
    } else if (!relationType.compare(">")) {
        this->relationType = RelationTypeEnum::GREATER;
    } else if (!relationType.compare(">=")) {
        this->relationType = RelationTypeEnum::EGREATER;
    } else if (!relationType.compare("<")) {
        this->relationType = RelationTypeEnum::LESS;
    } else if (!relationType.compare("<=")) {
        this->relationType = RelationTypeEnum::ELESS;
    }
}

bool RelationCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    
}
