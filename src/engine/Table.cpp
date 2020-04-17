#pragma once

#include "Table.h"

Table::Table() {}

Table::Table(string name, vector<TableField*> fields) {
    this->name = name;
    this->fields = fields;
}

Table::Table(string name, vector<TableField*> fields, vector<vector<DataType*> > rows) {
    this->name = name;
    this->fields = fields;
    this->rows = rows;
}

vector<TableField*> Table::getFields() {
    return this->fields;
}

vector<vector<DataType*> > Table::getRows() {
    return this->rows;
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
    for (vector<DataType*> row: table.rows) {
        cout << "    ";
        for (DataType* value: row) {
            cout << value->toString() << "  ";
        }
        cout << endl;
    }
    out << "  ]" << endl;

    out << "}";

    return out;
}