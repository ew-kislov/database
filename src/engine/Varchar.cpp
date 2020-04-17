#pragma once

#include <string>

#include "DataTypeEnum.h"

#include "EngineStatusEnum.h"
#include "EngineException.cpp"

#include "Varchar.h"

using namespace std;

void Varchar::parse(string valueString) {
    if (valueString[0] != '\'' || valueString[valueString.size() - 1] != '\'') {
        throw EngineException(EngineStatusEnum::InvalidValue);
    }

    this->value = valueString.substr(1, valueString.size() - 2);
}

Varchar::Varchar(string valueString, bool shouldParse) : DataType(DataTypeEnum::VARCHAR) {
    if (shouldParse) {
        parse(valueString);
    } else {
        this->value = valueString;
    }
}

string Varchar::toString() {
    return '\'' + this->value + '\'';
}

string Varchar::getValue() {
    return this->value;
}

bool Varchar::operator == (const Varchar &string) const {
    return this->value == string.value;
}
bool Varchar::operator == (const string stringValue) const {
    return this->value == stringValue;
}

bool Varchar::operator > (const Varchar &string) const {
    return this->value > string.value;
}
bool Varchar::operator > (const string stringValue) const {
    return this->value > stringValue;
}

bool Varchar::operator < (const Varchar &string) const {
    return this->value < string.value;
}
bool Varchar::operator < (const string stringValue) const {
    return this->value < stringValue;
}

bool Varchar::operator >= (const Varchar &string) const {
    return this->value >= string.value;
}
bool Varchar::operator >= (const string stringValue) const {
    return this->value >= stringValue;
}

bool Varchar::operator <= (const Varchar &string) const {
    return this->value <= string.value;
}
bool Varchar::operator <= (const string stringValue) const {
    return this->value <= stringValue;
}

bool Varchar::operator != (const Varchar &string) const {
    return this->value != string.value;
}
bool Varchar::operator != (const string stringValue) const {
    return this->value != stringValue;
}