#include "heavyhiggs/branch/Cut.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

Cut::Cut()
{
    Ht = InitialValue();
    EtMiss = InitialValue();
    NumberJet = static_cast<int>(InitialValue());
    NumberBottom = static_cast<int>(InitialValue());
    InvariantMass = InitialValue();
    DeltaR = InitialValue();
    LeptonPt1 = InitialValue();
    LeptonPt2 = InitialValue();
    BottomMinPt = InitialValue();
    BottomMaxRap = InitialValue();
}

Observables Cut::Variables()
{
    return OBSERVABLE(Ht) + OBSERVABLE(EtMiss)/* + OBSERVABLE(NumberJet) + OBSERVABLE(NumberBottom)*/ + OBSERVABLE(LeptonPt1) + OBSERVABLE(LeptonPt2);
}

}

}

