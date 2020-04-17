#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>

#include "TableField.h"
#include "DataType.h"

using namespace std;

class Table {
    private:
        string name;
        vector<TableField*> fields;
        vector<vector<DataType*> > rows;
    public:
        Table();
        Table(string name, vector<TableField*> fields);
        Table(string name, vector<TableField*> fields, vector<vector<DataType*> > rows);

        vector<TableField*> getFields();
        vector<vector<DataType*> > getRows();

        friend ostream& operator<< (ostream &out, const Table &table);
};

#endif