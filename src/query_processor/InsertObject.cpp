#pragma once

#include "InsertObject.h"

InsertObject::InsertObject(string table): QueryObject(QueryTypeEnum::Insert, table) {

}

void InsertObject::setFieldValues(vector<DataType*> fieldValues) {
    this->fieldValues = fieldValues;
}

vector<DataType*> InsertObject::getFieldValues() {
    return this->fieldValues;
}

string InsertObject::toString() {
    string insertString;
    
    insertString += "InsertObject {\n";
    insertString += "\ttable: " + getTable() + ",\n";
    insertString += "\tfieldValues: [\n";
    
    for (int i = 0; i < fieldValues.size(); ++i) {
        insertString += "\t\t" + fieldValues[i]->toString();
        
        if (i != fieldValues.size() - 1) {
            insertString += ",";
        }
        
        insertString += "\n";
    }
    
    insertString += "\t]\n";
    insertString += "}\n";
    
    return insertString;
}
