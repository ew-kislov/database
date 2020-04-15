#include "RelationCondition.h"

#include <string>

RelationCondition::RelationCondition(BaseOperand* operand1, BaseOperand* operand2, string relationType) : BinaryCondition(operand1, operand2) {
    if (!relationType.compare("=")) {
        this->relationType = 
    }
}
