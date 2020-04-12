#pragma once

#include "QueryObject.h"

QueryTypeEnum QueryObject::getType() {
    return this->type;
}

string QueryObject::getTable() {
    return this->table;
}