#pragma once

#include "NegatableCondition.h"

bool NegatableCondition::negate() {
    isNegated = !isNegated;
}