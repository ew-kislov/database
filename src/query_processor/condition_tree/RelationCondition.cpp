#include "RelationCondition.h"

#include "../../engine/Varchar.cpp"

#include <string>

// TODO: put in another file
DataType* getDataTypeOperand(int fieldIndex, vector<DataType*> row, BaseOperand* operand) {
    if (fieldIndex != -1) {
        return row[fieldIndex];
    } else {
        if (operand->getType() == OperandTypeEnum::NUMBER) {
            return new Number(dynamic_cast<NumberOperand*>(operand)->getValue());
        } else {
            return new Varchar(dynamic_cast<StringOperand*>(operand)->getValue());
        }
    }
}

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
    int fieldIndex1 = -1, fieldIndex2 = -1;
    
    if (
        operand1->getType() == OperandTypeEnum::TABLE_FIELD &&
        operand2->getType() == OperandTypeEnum::TABLE_FIELD
    ) {
        TableFieldOperand* fieldOperand1 = dynamic_cast<TableFieldOperand*>(operand1);
        TableField* field1;
        
        field1 = new TableField(fieldOperand1->getValue(), DataTypeEnum::VARCHAR);
        fieldIndex1 = VectorHelper::findInVector(fields, *field1);
            
        if (fieldIndex1 == -1) {
            field1 = new TableField(fieldOperand1->getValue(), DataTypeEnum::NUMBER);
            fieldIndex1 = VectorHelper::findInVector(fields, *field1);
                
            if (fieldIndex1 == -1) {
                cout << "Couldn't find field with this type";
                // TODO: throw exception
            }
        }
            
        TableFieldOperand* fieldOperand2 = dynamic_cast<TableFieldOperand*>(operand2);
        TableField* field2 = new TableField(fieldOperand2->getValue(), field1->getType());
        fieldIndex2 = VectorHelper::findInVector(fields, *field2);
            
        if (fieldIndex2 == -1) {
            cout << "Couldn't find field with this type" << endl;
            // TODO: throw exception
        }
            
    } else if (operand1->getType() == OperandTypeEnum::TABLE_FIELD) {
        TableFieldOperand* fieldOperand = dynamic_cast<TableFieldOperand*>(operand1);
        TableField* field;
        
        if (operand2->getType() == OperandTypeEnum::NUMBER) {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::NUMBER);
        } else {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::VARCHAR);
        }
        
        fieldIndex1 = VectorHelper::findInVector(fields, *field);
        
        if (fieldIndex1 == -1) {
            cout << "Couldn't find field with this type" << endl;
            // TODO: throw exception
        }
    
    } else if (operand2->getType() == OperandTypeEnum::TABLE_FIELD) {
        TableFieldOperand* fieldOperand = dynamic_cast<TableFieldOperand*>(operand2);
        TableField* field;
        
        if (operand1->getType() == OperandTypeEnum::NUMBER) {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::NUMBER);
        } else {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::VARCHAR);
        }
        
        fieldIndex2 = VectorHelper::findInVector(fields, *field);
            
        if (fieldIndex2 == -1) {
            cout << "Couldn't find field with this type" << endl;
            // TODO: throw exception
        }
    }
    
    DataType* dataTypeOperand1 = getDataTypeOperand(fieldIndex1, row, operand1);
    DataType* dataTypeOperand2 = getDataTypeOperand(fieldIndex2, row, operand2);
    
    if (dataTypeOperand1->getType() != dataTypeOperand2->getType()) {
        cout << "Relation operand types don't match" << endl;
        // TODO: throw exception
    }
    
    switch (relationType) {
        case EQ: return operand1 == operand2;
        case NEQ: return operand1 != operand2;
        case GREATER: return operand1 > operand2;
        case EGREATER: return operand1 >= operand2;
        case LESS:  return operand1 < operand2;
        case ELESS:  return operand1 <= operand2;
    }
}
