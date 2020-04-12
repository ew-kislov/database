#pragma once

#include "DataType.h"

void DataType::parse(string valueString) {
    throw "DataType: parse() not supported";
}

DataType::DataType(string valueString) { }

string DataType::toString() {
    throw "DataType: toString() not supported";
}

bool DataType::operator == (const DataType &dataType) const {
    throw "DataType: operator==() not supported";
}
bool DataType::operator == (const long double numberValue) const {
    throw "DataType: operator==() not supported";
}
bool DataType::operator == (const string stringValue) const {
    throw "DataType: operator==() not supported";
}

bool DataType::operator > (const DataType &dataType) const {
    throw "DataType: operator>() not supported";
}
bool DataType::operator > (const long double numberValue) const {
    throw "DataType: operator>() not supported";
}
bool DataType::operator > (const string stringValue) const {
    throw "DataType: operator>() not supported";
}

bool DataType::operator < (const DataType &dataType) const {
    throw "DataType: operator<() not supported";
}
bool DataType::operator < (const long double numberValue) const {
    throw "DataType: operator<() not supported";
}
bool DataType::operator < (const string stringValue) const {
    throw "DataType: operator<() not supported";
}


bool DataType::operator >= (const DataType &dataType) const {
    throw "DataType: operator>=() not supported";
}
bool DataType::operator >= (const long double numberValue) const {
    throw "DataType: operator>=() not supported";
}
bool DataType::operator >= (const string stringValue) const {
    throw "DataType: operator>=() not supported";
}

bool DataType::operator <= (const DataType &dataType) const {
    throw "DataType: operator<=() not supported";
}
bool DataType::operator <= (const long double numberValue) const {
    throw "DataType: operator<=() not supported";
}
bool DataType::operator <= (const string stringValue) const {
    throw "DataType: operator<=() not supported";
}

bool DataType::operator != (const DataType &dataType) const {
    throw "DataType: operator!=() not supported";
}
bool DataType::operator != (const long double numberValue) const {
    throw "DataType: operator!=() not supported";
}
bool DataType::operator != (const string stringValue) const {
    throw "DataType: operator!=() not supported";
}