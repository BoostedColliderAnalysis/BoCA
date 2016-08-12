#include "include/branch/CutNeutral.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

CutNeutral::CutNeutral()
{
    JetPt1 = InitialValue();
    JetPt2 = InitialValue();
    JetPt3 = InitialValue();
    JetPt4 = InitialValue();
    Ht = InitialValue();
    BottomNumber = static_cast<int>(InitialValue());
    LeptonPt = InitialValue();
}

Observables CutNeutral::Variables()
{
    return OBSERVABLE(JetPt1) + OBSERVABLE(JetPt2) +  OBSERVABLE(JetPt3) + OBSERVABLE(JetPt4) +  OBSERVABLE(Ht) + OBSERVABLE(BottomNumber) + OBSERVABLE(LeptonPt);
}

}

}

