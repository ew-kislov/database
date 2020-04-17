#pragma once

#include "DataTypeEnum.h"

#include "EngineException.h"

#include "Number.h"

using namespace std;

void Number::parse(string valueString) {
    try {
        this->value = stold(valueString);
    } catch(const exception& e) {
        throw EngineException("Number.parse(): wrong number value");
    }
}

Number::Number(string valueString) : DataType(DataTypeEnum::NUMBER) {
    parse(valueString);
}

Number::Number(int value) : DataType(DataTypeEnum::NUMBER) {
    this->value = value;
}

long double Number::getValue() {
    return value;
}

string Number::toString() {
    return to_string(this->value);
}

bool Number::operator == (const Number &number) const {
    return this->value == number.value;
}
bool Number::operator == (const long double numberValue) const {
    return this->value == numberValue;
}

bool Number::operator > (const Number &number) const {
    return this->value > number.value;
}
bool Number::operator > (const long double numberValue) const {
    return this->value > numberValue;
}

bool Number::operator < (const Number &number) const {
    return this->value < number.value;
}
bool Number::operator < (const long double numberValue) const {
    return this->value < numberValue;
}

bool Number::operator >= (const Number &number) const {
    return this->value >= number.value;
}
bool Number::operator >= (const long double numberValue) const {
    return this->value >= numberValue;
}

bool Number::operator <= (const Number &number) const {
    return this->value <= number.value;
}
bool Number::operator <= (const long double numberValue) const {
    return this->value <= numberValue;
}

bool Number::operator != (const Number &number) const {
    return this->value != number.value;
}
bool Number::operator != (const long double numberValue) const {
    return this->value != numberValue;
}