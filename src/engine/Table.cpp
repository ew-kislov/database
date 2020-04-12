#pragma once

#include "Table.h"

Table::Table() {}

Table::Table(string name, vector<TableField> fields) {
    this->name = name;
    this->fields = fields;
}

Table::Table(string name, vector<TableField> fields, vector<vector<DataType*> > rows) {
    this->name = name;
    this->fields = fields;
    this->rows = rows;
}

vector<TableField> Table::getFields() {
    return this->fields;
}

vector<vector<DataType*> > Table::getRows() {
    return this->rows;
}