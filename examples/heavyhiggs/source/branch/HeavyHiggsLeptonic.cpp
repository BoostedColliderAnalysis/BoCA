#include "heavyhiggs/branch/HeavyHiggsLeptonic.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

HeavyHiggsLeptonic::HeavyHiggsLeptonic()
{
    LargerWDeltaRap = InitialValue();
    LargerWDeltaPhi = InitialValue();
    LargerWDeltaR = InitialValue();
    SmallerWDeltaRap = InitialValue();
    SmallerWDeltaPhi = InitialValue();
    SmallerWDeltaR = InitialValue();
    LargerNeutrinoDeltaRap = InitialValue();
    LargerNeutrinoDeltaPhi = InitialValue();
    LargerNeutrinoDeltaR = InitialValue();
    SmallerNeutrinoDeltaRap = InitialValue();
    SmallerNeutrinoDeltaPhi = InitialValue();
    SmallerNeutrinoDeltaR = InitialValue();
}

boca::Observables HeavyHiggsLeptonic::Variables()
{
    return Particle::Variables() + OBSERVABLE(LargerWDeltaR) + OBSERVABLE(LargerWDeltaRap) + OBSERVABLE(LargerWDeltaPhi) + OBSERVABLE(SmallerWDeltaR) + OBSERVABLE(SmallerWDeltaRap) + OBSERVABLE(SmallerWDeltaPhi) + OBSERVABLE(LargerNeutrinoDeltaR) + OBSERVABLE(LargerNeutrinoDeltaRap) + OBSERVABLE(LargerNeutrinoDeltaPhi) + OBSERVABLE(SmallerNeutrinoDeltaR) + OBSERVABLE(SmallerNeutrinoDeltaRap) + OBSERVABLE(SmallerNeutrinoDeltaPhi);
}

}

}

