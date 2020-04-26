#pragma once

#include "CreateObject.h"

CreateObject::CreateObject(string table, vector<TableField*> tableFields): QueryObject(QueryTypeEnum::Create, table) {
    this->tableFields = tableFields;
}

vector<TableField*> CreateObject::getTableFields() {
    return this->tableFields;
}

string CreateObject::toString() {
    string createString;
    
    createString += "CreateObject {\n";
    createString += "\ttable: " + getTable() + ",\n";
    createString += "\ttableFields: [\n";
    
    for (int i = 0; i < tableFields.size(); ++i) {
        createString += "\t\t" + tableFields[i]->toString();
        
        if (i != tableFields.size() - 1) {
            createString += ",";
        }
        
        createString += "\n";
    }
    
    createString += "\t]\n";
    createString += "}\n";
    
    return createString;
}
