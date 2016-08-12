#include "include/branch/EventNeutral.hh"
#include "boca/OBSERVABLE.hh"

namespace heavyhiggs
{

namespace branch
{

EventNeutral::EventNeutral()
{
    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
//     BottomBdt = InitialValue();
//     PairBottomBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
//     BottomBdt1 = InitialValue();
//     BottomBdt2 = InitialValue();
//     BottomBdt3 = InitialValue();
//     BottomBdt4 = InitialValue();
//     BottomBdt5 = InitialValue();
//     BottomBdt6 = InitialValue();
//     BottomBdt7 = InitialValue();
//     BottomBdt8 = InitialValue();
//     BottomBdt12 = InitialValue();
//     BottomBdt34 = InitialValue();
//     BottomBdt56 = InitialValue();
//     BottomBdt78 = InitialValue();
}

Observables EventNeutral::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap)/* + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78)*/;
}

}

}

