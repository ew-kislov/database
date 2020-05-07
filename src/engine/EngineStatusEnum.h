#ifndef ENGINE_STATUS_H
#define ENGINE_STATUS_H

enum EngineStatusEnum {
    TableAlreadyExists = 1,
    NoPermission = 2,
    TableDoesNotExist = 3,
    TableStructureCorrupted = 4,
    WrongValuesNumber = 5,
    WrongValueType = 6,
    InvalidValue = 7,
    NoSuchField = 8,
    FieldValueTypesDontMatch = 9,
    InternalError = 10,
};

#endif
