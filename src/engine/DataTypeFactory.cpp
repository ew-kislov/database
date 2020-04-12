#pragma once

#include <string>

#include "DataTypeEnum.h"
#include "DataType.cpp"
#include "Varchar.cpp"
#include "Number.cpp"

using namespace std;

namespace DataTypeFactory {
    DataType* create(string valueString, DataTypeEnum dataTypeEnum) {
        if (dataTypeEnum == DataTypeEnum::Number) {
            return new Number(valueString);
        } else if (dataTypeEnum == DataTypeEnum::Varchar) {
            return new Varchar(valueString);
        }
    }
}