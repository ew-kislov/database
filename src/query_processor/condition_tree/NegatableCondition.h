#ifndef NEGATABLE_CONDITION_H
#define NEGATABLE_CONDITION_H

using namespace std;

class NegatableCondition {
    protected:
        bool isNegated;
    public:
        NegatableCondition(bool doNegated = false);
    
        bool negate();
};

#endif
