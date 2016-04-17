#include "GAMultiplier.h"
#include "ToffoliGate.h"


GAMultiplier::GAMultiplier () : Multiplier ()
{
    return;
}


GAMultiplier::GAMultiplier (std::vector<ToffoliGate *> gates) : Multiplier ()
{
    this->gates = gates;
}


GAMultiplier::~GAMultiplier ()
{
    return;
}
