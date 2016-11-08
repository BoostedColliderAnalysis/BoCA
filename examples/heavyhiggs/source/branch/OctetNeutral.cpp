#include "heavyhiggs/branch/OctetNeutral.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

OctetNeutral::OctetNeutral()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
//     BottomBdt = InitialValue();
//     PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}

Observables OctetNeutral::Variables()
{
    return Multi::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap) + /*OBSERVABLE(BottomBdt) +*/ OBSERVABLE(HardTopPt) + OBSERVABLE(SoftTopPt) /*+ OBSERVABLE(PairBottomBdt)*/;
}

}

}

