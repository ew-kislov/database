#include "DropObject.h"

DropObject::DropObject(string table): QueryObject(QueryTypeEnum::Drop, table) {
    
}
