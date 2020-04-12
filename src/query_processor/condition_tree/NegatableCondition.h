#ifndef NEGATABLE_CONDITION_H
#define NEGATABLE_CONDITION_H

using namespace std;

class NegatableCondition {
    protected:
        bool isNegated = false;
    public:
        bool negate();
};

#endif