#pragma once

#include "Table.h"

Table::Table() {}

Table::Table(string name, vector<TableField*> fields) {
    this->name = name;
    this->fields = fields;
}

Table::Table(string name, vector<TableField*> fields, int headerOffset) {
    this->name = name;
    this->fields = fields;
    this->headerOffset = headerOffset;
}

Table::Table(string name, vector<TableField*> fields, vector<TableRow> rows, int headerOffset) {
    this->name = name;
    this->fields = fields;
    this->rows = rows;
    this->headerOffset = headerOffset;
}

vector<TableField*> Table::getFields() {
    return this->fields;
}

vector<TableRow> Table::getRows() {
    return this->rows;
}

string Table::getName() {
    return name;
}

int Table::getHeaderOffset() {
    return headerOffset;
}

ostream& operator<< (ostream &out, const Table &table) {
    out << "Table {" << endl;
    out << "  name: " << table.name << "," << endl;

    out << "  fields: [" << endl;
    for (TableField* field : table.fields) {
        out << "    " << field->toString() << endl;
    }
    out << "  ]" << endl;

    out << "  rows: [" << endl;
    for (TableRow row: table.rows) {
        cout << "    " <<row.toString() << endl;
    }
    out << "  ]" << endl;

    out << "}";

    return out;
}