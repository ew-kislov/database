#ifndef NEGATABLE_CONDITION_H
#define NEGATABLE_CONDITION_H

using namespace std;

class NegatableCondition {
    protected:
        bool isNegated;
    public:
        NegatableCondition(bool isNegated = false);
    
        bool negate();
        string toString();
};

#endif
