#include "heavyhiggs/branch/OctetCharged.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

OctetCharged::OctetCharged()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
//     BottomBdt = InitialValue();
//     PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

Observables OctetCharged::Variables()
{
    return Multi::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap)/* + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt)*/;
}

}

}

