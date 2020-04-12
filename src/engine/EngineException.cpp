#pragma once

#include "EngineException.h"

#include <iostream>
#include <exception>

EngineException::EngineException(string message) : message(message) {}

const char* EngineException::what() const throw () {
    return message.c_str();
}

EngineException::~EngineException() throw() {}