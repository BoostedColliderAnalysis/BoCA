#include "higgscpv/branch/SignatureLeptonic.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace higgscpv
{

namespace branch
{

SignatureLeptonic::SignatureLeptonic()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    Aplanarity = InitialValue();
    Sphericity = InitialValue();
}

Observables SignatureLeptonic::Variables()
{
    return Multi::Variables() + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(HardTopPt) + OBSERVABLE(SoftTopPt) + OBSERVABLE(HiggsMass) + OBSERVABLE(PairRap) + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity);
}

}

}

