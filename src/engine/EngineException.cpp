#pragma once

#include "EngineException.h"

#include <iostream>
#include <exception>

EngineException::EngineException(EngineStatusEnum status) {
    this->status = status;
}

const char* EngineException::what() const throw () {
    return to_string(static_cast<int>(status)).c_str();
}

int EngineException::getStatus() {
    return status;
}

EngineException::~EngineException() throw() {}