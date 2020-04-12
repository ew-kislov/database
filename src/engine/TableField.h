#ifndef TABLE_FIELD_H
#define TABLE_FIELD_H

#include <string>

#include "DataTypeEnum.h"

using namespace std;

class TableField {
    private:
        string name;
        DataTypeEnum type;
    public:
        TableField(string name, DataTypeEnum type);

        string getName();
        DataTypeEnum getType();
};

#endif