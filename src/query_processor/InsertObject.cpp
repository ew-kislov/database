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
    return "";
}