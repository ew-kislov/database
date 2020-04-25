#pragma once

#include "CreateObject.h"

CreateObject::CreateObject(string table, vector<TableField> tableFields): QueryObject(QueryTypeEnum::Create, table) {
    this->tableFields = tableFields;
}

vector<TableField> CreateObject::getTableFields() {
    return this->tableFields;
}

string CreateObject::toString() {
    string createString;
    
    createString += "CreateObject {\n";
    createString += "\ttableFields:\n";
    
    for (TableField it: tableFields) {
        createString += "\t\t" + it.toString() + "\n";
    }
    createString += "}";
    
    return createString;
}
