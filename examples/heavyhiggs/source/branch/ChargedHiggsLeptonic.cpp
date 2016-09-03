#include "heavyhiggs/branch/ChargedHiggsLeptonic.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

ChargedHiggsLeptonic::ChargedHiggsLeptonic()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
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
    TopBdt = InitialValue();
    HeavyHiggsTag = static_cast<int>(InitialValue());
}

Observables ChargedHiggsLeptonic::Variables()
{
    return Particle::Variables() + OBSERVABLE(HeavyHiggsMass) + OBSERVABLE(HeavyHiggsPt) + OBSERVABLE(TopDeltaR) + OBSERVABLE(TopDeltaRap) + OBSERVABLE(TopDeltaPhi) + OBSERVABLE(TopBdt);
}

Observables ChargedHiggsLeptonic::Spectators()
{
    return Particle::Spectators() + OBSERVABLE(HeavyHiggsTag);
}

}

}

