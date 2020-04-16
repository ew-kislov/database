#pragma once

#include "NegatableCondition.h"

NegatableCondition::NegatableCondition(bool doNegated) {
    this->isNegated = doNegated;
}

bool NegatableCondition::negate() {
    isNegated = !isNegated;
}
