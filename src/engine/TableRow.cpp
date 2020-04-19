#pragma once

#include "TableRow.h"

TableRow::TableRow() {
    deleted = false;
}

void TableRow::addValue(DataType* value) {
    values.push_back(value);
}

bool TableRow::isDeleted() {
    return deleted;
}

void TableRow::setDeleted() {
    deleted = true;
}

vector<DataType*> TableRow::getValues() {
    return values;
}

string TableRow::toString() {
    string rowString;

    rowString += "TableRow { values: [ ";
    for (int i = 0; i < values.size(); i++) {
        rowString += values[i]->toString();
        if (i != values.size() - 1) {
            rowString += ", ";
        }
    }
    rowString += " ], deleted: ";
    rowString += deleted ? "true" : "false";
    rowString += " }";

    return rowString;
}