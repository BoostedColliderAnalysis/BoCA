#include "Branch.hh"
#include "Pair.hh"

namespace analysis {

namespace heavyhiggs {

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
analysis::Observables HeavyHiggsLeptonicBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(LargerWDeltaR), PAIR(LargerWDeltaRap), PAIR(LargerWDeltaPhi), PAIR(SmallerWDeltaR), PAIR(SmallerWDeltaRap), PAIR(SmallerWDeltaPhi), PAIR(LargerNeutrinoDeltaR), PAIR(LargerNeutrinoDeltaRap), PAIR(LargerNeutrinoDeltaPhi), PAIR(SmallerNeutrinoDeltaR), PAIR(SmallerNeutrinoDeltaRap), PAIR(SmallerNeutrinoDeltaPhi)});
}

HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
    Flag = int(InitialValue());
}
Observables ChargedHiggsSemiBranch::Spectators() const
{
    return Join(ParticleBranch::Spectators(), {PAIR(Flag)});
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
Observables ChargedHiggsLeptonicBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(HeavyHiggsMass), PAIR(HeavyHiggsPt), PAIR(TopDeltaR), PAIR(TopDeltaRap), PAIR(TopDeltaPhi), PAIR(TopBdt)});
}
Observables ChargedHiggsLeptonicBranch::Spectators() const
{
    return Join(ParticleBranch::Spectators(), {PAIR(HeavyHiggsTag)});
}

HeavyHiggsTauBranch::HeavyHiggsTauBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}
Observables HeavyHiggsTauBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(LeptonPt), PAIR(NeutrinoPt)});
}

EventNeutralBranch::EventNeutralBranch()
{
    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBdt = InitialValue();
    PairBottomBdt = InitialValue();
    JetRestNumber = int(InitialValue());
    BdtSum = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    RestBottomBdt1 = InitialValue();
    RestBottomBdt2 = InitialValue();
    RestBottomBdt3 = InitialValue();
    RestBottomBdt4 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
    Planarity = InitialValue();
    Dipolarity1 = InitialValue();
    Dipolarity2 = InitialValue();
    Pull1 = InitialValue();
    Pull2 = InitialValue();
//     BottomBdt12 = InitialValue();
//     BottomBdt34 = InitialValue();
//     BottomBdt56 = InitialValue();
//     BottomBdt78 = InitialValue();
}
Observables EventNeutralBranch::Variables() const
{
  return Join(MultiBranch::Variables(), {PAIR(JetNumber), PAIR(BottomNumber), PAIR(ScalarHt),PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi), PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(SoftTopPt), PAIR(HardTopPt),PAIR(JetRestNumber), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(RestBottomBdt1), PAIR(RestBottomBdt2)});
  
//   return Join(EventBranch::Variables(),{PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(SoftTopPt), PAIR(HardTopPt),PAIR(JetRestNumber)/*,PAIR(BottomBdt1), PAIR(BottomBdt2)*/, PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(RestBottomBdt1), PAIR(RestBottomBdt2)/*,PAIR(Pull1), PAIR(Pull2)*/ /*PAIR(RestBottomBdt3), PAIR(RestBottomBdt4)*//*, PAIR(Sphericity), PAIR(Aplanarity), PAIR(Planarity)*/});
    
//   return Join(ParticleBranch::Variables(), {PAIR(HiggsMass),  PAIR(HiggsBdt),PAIR(PairBdt),PAIR(PairRap),PAIR(Bdt1, "BDT_{1}"),PAIR(Bdt2, "BDT_{Bdt2}"), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"),PAIR(DeltaHt,"#DeltaH_{T}"),/*PAIR(LeptonNumber),*/PAIR(BottomNumber),PAIR(JetRestNumber),PAIR(SoftTopPt), PAIR(HardTopPt),/*PAIR(MissingEt),*/ PAIR(ScalarHt), /*PAIR(LeptonHt),*/ PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi), PAIR(JetNumber)/*,PAIR(BdtSum)*//*,PAIR(BottomBdt1), PAIR(BottomBdt2)*//*, PAIR(BottomBdt3)*/, PAIR(BottomBdt4), PAIR(RestBottomBdt1), PAIR(RestBottomBdt2), PAIR(RestBottomBdt3)/*, PAIR(RestBottomBdt4)*//*, PAIR(Sphericity), PAIR(Aplanarity), PAIR(Planarity)*/});

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
Observables EventNeutralFourTopBranch::Variables() const
{
  return Join(MultiBranch::Variables(), {PAIR(JetNumber), PAIR(BottomNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi),PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56)});
}

EventFusionBranch::EventFusionBranch()
{
    HiggsMass = InitialValue();
}
Observables EventFusionBranch::Variables() const
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass)});
}

OctetNeutralBranch::OctetNeutralBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    BdtSum = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}
Observables OctetNeutralBranch::Variables() const
{
  // tttt
  return Join(MultiBranch::Variables(), {PAIR(HiggsMass),PAIR(PairRap), PAIR(BottomBdt),PAIR(HardTopPt),PAIR(SoftTopPt),PAIR(PairBottomBdt)});
  
  // ttbb
//   return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Bdt1, "BDT_{1}"), PAIR(Bdt2, "BDT_{2}"),PAIR(DeltaHt, "#Delta H_{T}"),PAIR(HiggsMass),PAIR(PairRap), PAIR(BottomBdt),PAIR(HardTopPt),PAIR(SoftTopPt)/*,PAIR(BdtSum)*/,PAIR(PairBottomBdt)});
}
Observables OctetChargedBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(HiggsMass), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt)});
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

Observables EventChargedBranch::Variables() const
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}
}
}

