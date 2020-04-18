#ifndef TABLE_ROW_H
#define TABLE_ROW_H

#include <vector>
#include <string>

#include "DataType.h"

using namespace std;

class TableRow {
    private:
        vector<DataType*> values;
        vector<DataType*> prevValues;
        bool deleted;

    public:
        TableRow();
        
        void addValue(DataType* value);

        bool isDeleted();
        void setDeleted();

        vector<DataType*> getValues();

        string toString();
};

#endif