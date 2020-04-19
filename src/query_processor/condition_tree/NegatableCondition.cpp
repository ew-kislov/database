#pragma once

#include "NegatableCondition.h"

NegatableCondition::NegatableCondition(bool isNegated) {
    this->isNegated = isNegated;
}

bool NegatableCondition::negate() {
    isNegated = !isNegated;
}
