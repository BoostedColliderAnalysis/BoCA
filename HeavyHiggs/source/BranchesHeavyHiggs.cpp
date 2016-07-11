#include "boca/BranchesHeavyHiggs.hh"
#include "boca/OBSERVABLE.hh"

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

boca::Observables HeavyHiggsLeptonicBranch::Variables()
{
    return Particle::Variables() + OBSERVABLE(LargerWDeltaR) + OBSERVABLE(LargerWDeltaRap) + OBSERVABLE(LargerWDeltaPhi) + OBSERVABLE(SmallerWDeltaR) + OBSERVABLE(SmallerWDeltaRap) + OBSERVABLE(SmallerWDeltaPhi) + OBSERVABLE(LargerNeutrinoDeltaR) + OBSERVABLE(LargerNeutrinoDeltaRap) + OBSERVABLE(LargerNeutrinoDeltaPhi) + OBSERVABLE(SmallerNeutrinoDeltaR) + OBSERVABLE(SmallerNeutrinoDeltaRap) + OBSERVABLE(SmallerNeutrinoDeltaPhi);
}

HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
//     Flag = static_cast<int>(InitialValue());
}

// Observables ChargedHiggsSemiBranch::Spectators()
// {
//     return Particle::Spectators() + OBSERVABLE(Flag);
// }

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
    HeavyHiggsTag = static_cast<int>(InitialValue());
}

Observables ChargedHiggsLeptonicBranch::Variables()
{
    return Particle::Variables() + OBSERVABLE(HeavyHiggsMass) + OBSERVABLE(HeavyHiggsPt) + OBSERVABLE(TopDeltaR) + OBSERVABLE(TopDeltaRap) + OBSERVABLE(TopDeltaPhi) + OBSERVABLE(TopBdt);
}

Observables ChargedHiggsLeptonicBranch::Spectators()
{
    return Particle::Spectators() + OBSERVABLE(HeavyHiggsTag);
}

HeavyHiggsTau::HeavyHiggsTau()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables HeavyHiggsTau::Variables()
{
    return Particle::Variables() + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
}

EventNeutralBranch::EventNeutralBranch()
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

Observables EventNeutralBranch::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap)/* + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78)*/;
}

EventNeutralFourTopBranch::EventNeutralFourTopBranch()
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

Observables EventNeutralFourTopBranch::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap) /*+ OBSERVABLE(BottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78)*/;
}

EventFusionBranch::EventFusionBranch()
{
    HiggsMass = InitialValue();
}

Observables EventFusionBranch::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass);
}

OctetNeutralBranch::OctetNeutralBranch()
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

Observables OctetNeutralBranch::Variables()
{
    return Multi::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap) + /*OBSERVABLE(BottomBdt) +*/ OBSERVABLE(HardTopPt) + OBSERVABLE(SoftTopPt) /*+ OBSERVABLE(PairBottomBdt)*/;
}

OctetChargedBranch::OctetChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
//     BottomBdt = InitialValue();
//     PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

Observables OctetChargedBranch::Variables()
{
    return Multi::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(PairBdt) + OBSERVABLE(PairRap)/* + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt)*/;
}

EventChargedBranch::EventChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
//     BottomBdt = InitialValue();
//     PairBottomBdt = InitialValue();
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

Observables EventChargedBranch::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass) + OBSERVABLE(HiggsBdt) + OBSERVABLE(SignatureBdt) + OBSERVABLE(PairRap) /*+ OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(BottomBdt1) + OBSERVABLE(BottomBdt2) + OBSERVABLE(BottomBdt3) + OBSERVABLE(BottomBdt4) + OBSERVABLE(BottomBdt5) + OBSERVABLE(BottomBdt6) + OBSERVABLE(BottomBdt7) + OBSERVABLE(BottomBdt8) + OBSERVABLE(BottomBdt12) + OBSERVABLE(BottomBdt34) + OBSERVABLE(BottomBdt56) + OBSERVABLE(BottomBdt78)*/;
}

HeavyHiggsCut::HeavyHiggsCut()
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

Observables HeavyHiggsCut::Variables()
{
    return OBSERVABLE(Ht) + OBSERVABLE(EtMiss)/* + OBSERVABLE(NumberJet) + OBSERVABLE(NumberBottom)*/ + OBSERVABLE(LeptonPt1) + OBSERVABLE(LeptonPt2);
}

HeavyHiggsCutNeutralBranch::HeavyHiggsCutNeutralBranch()
{
    JetPt1 = InitialValue();
    JetPt2 = InitialValue();
    JetPt3 = InitialValue();
    JetPt4 = InitialValue();
    Ht = InitialValue();
    BottomNumber = static_cast<int>(InitialValue());
    LeptonPt = InitialValue();
}

Observables HeavyHiggsCutNeutralBranch::Variables()
{
    return OBSERVABLE(JetPt1) + OBSERVABLE(JetPt2) +  OBSERVABLE(JetPt3) + OBSERVABLE(JetPt4) +  OBSERVABLE(Ht) + OBSERVABLE(BottomNumber) + OBSERVABLE(LeptonPt);
}

JetPairBranch::JetPairBranch()
{
  //     DeltaM = InitialValue();
  Jet1Mass = InitialValue();
  Jet1Pt = InitialValue();
  Jet1Rap = InitialValue();
  Jet1Phi = InitialValue();
  //     Jet1Bdt = InitialValue();
  //     Jet1BTag = InitialValue();
  Jet2Mass = InitialValue();
  Jet2Pt = InitialValue();
  Jet2Rap = InitialValue();
  Jet2Phi = InitialValue();
  //     Jet2Bdt = InitialValue();
  //     Jet2BTag = InitialValue();
  //     BdtRatio11 = InitialValue();
  //     BdtRatio12 = InitialValue();
  //     BdtRatio13 = InitialValue();
  //     BdtRatio14 = InitialValue();
  //     BdtRatio21 = InitialValue();
  //     BdtRatio22 = InitialValue();
  //     BdtRatio23 = InitialValue();
  //     BdtRatio24 = InitialValue();
}


Observables JetPairBranch::Variables()
{
  return TwoBody::Variables() + OBSERVABLE(Jet1Mass) + OBSERVABLE(Jet1Pt) + OBSERVABLE(Jet1Rap) + OBSERVABLE(Jet1Phi) + OBSERVABLE(Jet2Mass) + OBSERVABLE(Jet2Pt) + OBSERVABLE(Jet2Rap) + OBSERVABLE(Jet2Phi);
}



TripletJetPairBranch::TripletJetPairBranch()
{
  BottomMass = InitialValue();
  BottomPt = InitialValue();
  BottomRap = InitialValue();
  BottomPhi = InitialValue();
  BottomBdt = InitialValue();
  BottomBTag = InitialValue();
  TopMass = InitialValue();
  TopPt = InitialValue();
  TopRap = InitialValue();
  TopPhi = InitialValue();
  TopBdt = InitialValue();
  TopBTag = InitialValue();
}

Observables TripletJetPairBranch::Variables()
{
  return TwoBody::Variables() + OBSERVABLE(BottomPt) + OBSERVABLE(BottomRap) + OBSERVABLE(BottomPhi) + OBSERVABLE(BottomMass) + OBSERVABLE(TopPt) + OBSERVABLE(TopRap) + OBSERVABLE(TopPhi) + OBSERVABLE(TopMass) + OBSERVABLE(TopBdt);
}

}

}

