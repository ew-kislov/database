#pragma once

#include "NegatableCondition.h"

NegatableCondition::NegatableCondition(bool isNegated) {
    this->isNegated = isNegated;
}

bool NegatableCondition::negate() {
    isNegated = !isNegated;
}

string NegatableCondition::toString() {
    string message = "NOT";
    return message;
}
