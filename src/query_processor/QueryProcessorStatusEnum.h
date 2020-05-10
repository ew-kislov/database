#ifndef QUERY_PROCESSOR_STATUS_ENUM_H
#define QUERY_PROCESSOR_STATUS_ENUM_H

enum QueryProcessorStatusEnum {
    Success = 1,
    UnknownCommand = 2,
    NoColumnWithGivenType = 3
};

#endif