#include "Branch.hh"
#include "Pair.hh"

namespace boca
{

namespace heavyhiggs
{

HeavyHiggsLeptonicBranch::HeavyHiggsLeptonicBranch()
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

HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
//     Flag = int(InitialValue());
}

ChargedHiggsLeptonicBranch::ChargedHiggsLeptonicBranch()
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
    HeavyHiggsTag = int(InitialValue());
}

HeavyHiggsTauBranch::HeavyHiggsTauBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

EventNeutralBranch::EventNeutralBranch()
{
    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();
}

EventNeutralFourTopBranch::EventNeutralFourTopBranch()
{
    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();
}

EventFusionBranch::EventFusionBranch()
{
    HiggsMass = InitialValue();
}

OctetNeutralBranch::OctetNeutralBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}

OctetChargedBranch::OctetChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

EventChargedBranch::EventChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();
}


boca::Observables HeavyHiggsLeptonicBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(LargerWDeltaR) + OBSERVABLE(LargerWDeltaRap) + OBSERVABLE(LargerWDeltaPhi) + OBSERVABLE(SmallerWDeltaR) + OBSERVABLE(SmallerWDeltaRap) + OBSERVABLE(SmallerWDeltaPhi) + OBSERVABLE(LargerNeutrinoDeltaR) + OBSERVABLE(LargerNeutrinoDeltaRap) + OBSERVABLE(LargerNeutrinoDeltaPhi) + OBSERVABLE(SmallerNeutrinoDeltaR) + OBSERVABLE(SmallerNeutrinoDeltaRap) + OBSERVABLE(SmallerNeutrinoDeltaPhi);
}
Observables ChargedHiggsLeptonicBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(HeavyHiggsMass) + OBSERVABLE(HeavyHiggsPt) + OBSERVABLE(TopDeltaR) + OBSERVABLE(TopDeltaRap) + OBSERVABLE(TopDeltaPhi) + OBSERVABLE(TopBdt);
}
Observables ChargedHiggsLeptonicBranch::Spectators()
{
    return ParticleBranch::Spectators() + OBSERVABLE(HeavyHiggsTag);
}
Observables HeavyHiggsTauBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
}
Observables EventNeutralBranch::Variables()
{
    return EventBranch::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap) + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78);
}
Observables EventFusionBranch::Variables()
{
    return EventBranch::Variables() + OBSERVABLE(HiggsMass);
}
Observables OctetNeutralBranch::Variables()
{
    return MultiBranch::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap) + OBSERVABLE(BottomBdt) + OBSERVABLE(HardTopPt) + OBSERVABLE(SoftTopPt) + OBSERVABLE(PairBottomBdt);
}
Observables OctetChargedBranch::Variables()
{
    return MultiBranch::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap) + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt);
}
Observables EventChargedBranch::Variables()
{
    return EventBranch::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap) + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78);
}
// Observables ChargedHiggsSemiBranch::Spectators()
// {
//     return ParticleBranch::Spectators() + OBSERVABLE(Flag);
// }
Observables EventNeutralFourTopBranch::Variables()
{
    return EventBranch::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap) + OBSERVABLE(BottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78);
}

HeavyHiggsCutBranch::HeavyHiggsCutBranch()
{
    Ht = InitialValue();
    EtMiss = InitialValue();
    NumberJet = int(InitialValue());
    NumberBottom = int(InitialValue());
    InvariantMass = InitialValue();
    DeltaR = InitialValue();
    LeptonPt1 = InitialValue();
    LeptonPt2 = InitialValue();
    BottomMinPt = InitialValue();
    BottomMaxRap = InitialValue();
}

Observables HeavyHiggsCutBranch::Variables()
{
    return OBSERVABLE(Ht) + OBSERVABLE(EtMiss)/* + OBSERVABLE(NumberJet) + OBSERVABLE(NumberBottom)*/ + OBSERVABLE(LeptonPt1) + OBSERVABLE(LeptonPt2);
}

HeavyHiggsCutNeutralBranch::HeavyHiggsCutNeutralBranch()
{
//   Ht = InitialValue();
//   EtMiss = InitialValue();
//   NumberJet = int(InitialValue());
//   NumberBottom = int(InitialValue());
//   InvariantMass = InitialValue();
//   DeltaR = InitialValue();
    LeptonPt1 = InitialValue();
    LeptonPt2 = InitialValue();
//   BottomMinPt = InitialValue();
//   BottomMaxRap = InitialValue();
}

Observables HeavyHiggsCutNeutralBranch::Variables()
{
    return OBSERVABLE(LeptonPt1) + OBSERVABLE(LeptonPt2);
}

}

}

