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
    return Join(ParticleBranch::Variables(), {PAIR(LargerWDeltaR), PAIR(LargerWDeltaRap), PAIR(LargerWDeltaPhi), PAIR(SmallerWDeltaR), PAIR(SmallerWDeltaRap), PAIR(SmallerWDeltaPhi), PAIR(LargerNeutrinoDeltaR), PAIR(LargerNeutrinoDeltaRap), PAIR(LargerNeutrinoDeltaPhi), PAIR(SmallerNeutrinoDeltaR), PAIR(SmallerNeutrinoDeltaRap), PAIR(SmallerNeutrinoDeltaPhi)});
}
Observables ChargedHiggsLeptonicBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(HeavyHiggsMass), PAIR(HeavyHiggsPt), PAIR(TopDeltaR), PAIR(TopDeltaRap), PAIR(TopDeltaPhi), PAIR(TopBdt)});
}
Observables ChargedHiggsLeptonicBranch::Spectators()
{
    return Join(ParticleBranch::Spectators(), {PAIR(HeavyHiggsTag)});
}
Observables HeavyHiggsTauBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(LeptonPt), PAIR(NeutrinoPt)});
}
Observables EventNeutralBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}
Observables EventFusionBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass)});
}
Observables OctetNeutralBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(HardTopPt), PAIR(SoftTopPt), PAIR(PairBottomBdt)});
}
Observables OctetChargedBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt)});
}
Observables EventChargedBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}
// Observables ChargedHiggsSemiBranch::Spectators()
// {
//     return Join(ParticleBranch::Spectators(), {PAIR(Flag)});
// }
Observables EventNeutralFourTopBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}

HeavyHiggsCutBranch::HeavyHiggsCutBranch()
{
  Ht = InitialValue();
  EtMiss = InitialValue();
  NumberJet = int(InitialValue());
  NumberBottom = int(InitialValue());
  InvariantMass = InitialValue();
  DeltaR = InitialValue();
}

Observables HeavyHiggsCutBranch::Variables()
{
  return {PAIR(Ht), PAIR(EtMiss), PAIR(NumberJet), PAIR(NumberBottom), PAIR(InvariantMass), PAIR(DeltaR)};
}

}

}

