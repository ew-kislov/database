#pragma once

#include <string>

#include "DataTypeEnum.h"
#include "DataType.cpp"
#include "Varchar.cpp"
#include "Number.cpp"

using namespace std;

namespace DataTypeFactory {
    DataType* create(string valueString, DataTypeEnum dataTypeEnum) {
        if (dataTypeEnum == DataTypeEnum::NUMBER) {
            return new Number(valueString);
        } else if (dataTypeEnum == DataTypeEnum::VARCHAR) {
            return new Varchar(valueString);
        }
    }

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
}
