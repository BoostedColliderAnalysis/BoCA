#include "BranchesHiggsCpv.hh"
#include "Pair.hh"

namespace analysis
{
namespace higgscpv
{

SignatureTTaggerBranch::SignatureTTaggerBranch()
{
    Bdt3 = InitialValue();
    Mass12 = InitialValue();
    Mass23 = InitialValue();
    Mass13 = InitialValue();
    DeltaPt23 = InitialValue();
    DeltaPt13 = InitialValue();
    Pt12 = InitialValue();
    Pt23 = InitialValue();
    Pt13 = InitialValue();
    Ht12 = InitialValue();
    Ht23 = InitialValue();
    Ht13 = InitialValue();
    Rho23 = InitialValue();
    Rho13 = InitialValue();
    DeltaRap23 = InitialValue();
    DeltaRap13 = InitialValue();
    DeltaPhi23 = InitialValue();
    DeltaPhi13 = InitialValue();
    DeltaR23 = InitialValue();
    DeltaR13 = InitialValue();
    DeltaM23 = InitialValue();
    DeltaM13 = InitialValue();
    DeltaHt23 = InitialValue();
    DeltaHt13 = InitialValue();
    Pull23 = InitialValue();
    Pull13 = InitialValue();
    DeltaPull23 = InitialValue();
    DeltaPull13 = InitialValue();
    Dipolarity23 = InitialValue();
    Dipolarity13 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureTTaggerBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(Bdt3), PAIR(Mass12), PAIR(Mass23), PAIR(Mass13), PAIR(Pt12), PAIR(Pt23), PAIR(Pt13), PAIR(DeltaPt23), PAIR(DeltaPt13), PAIR(Ht12), PAIR(Ht23), PAIR(Ht13), PAIR(Rho23), PAIR(Rho13), PAIR(DeltaRap23), PAIR(DeltaRap13), PAIR(DeltaPhi23), PAIR(DeltaPhi13), PAIR(DeltaR23), PAIR(DeltaR13), PAIR(DeltaM23), PAIR(DeltaM13), PAIR(DeltaHt23), PAIR(DeltaHt13), PAIR(Pull23), PAIR(Pull13), PAIR(DeltaPull23), PAIR(DeltaPull13), PAIR(Dipolarity23), PAIR(Dipolarity13), PAIR(Aplanarity), PAIR(Sphericity)});
}



SignatureLeptonTaggerBranch::SignatureLeptonTaggerBranch()
{
    Mass12 = InitialValue();
    Mass23 = InitialValue();
    Mass13 = InitialValue();
    DeltaPt23 = InitialValue();
    DeltaPt13 = InitialValue();
    Pt12 = InitialValue();
    Pt23 = InitialValue();
    Pt13 = InitialValue();
    Ht12 = InitialValue();
    Ht23 = InitialValue();
    Ht13 = InitialValue();
    Rho23 = InitialValue();
    Rho13 = InitialValue();
    DeltaRap23 = InitialValue();
    DeltaRap13 = InitialValue();
    DeltaPhi23 = InitialValue();
    DeltaPhi13 = InitialValue();
    DeltaR23 = InitialValue();
    DeltaR13 = InitialValue();
    DeltaM23 = InitialValue();
    DeltaM13 = InitialValue();
    DeltaHt23 = InitialValue();
    DeltaHt13 = InitialValue();
    Pull23 = InitialValue();
    Pull13 = InitialValue();
    DeltaPull23 = InitialValue();
    DeltaPull13 = InitialValue();
    Dipolarity23 = InitialValue();
    Dipolarity13 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureLeptonTaggerBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Rho, "#rho"), PAIR(Bdt1, "BDT_{1}"), PAIR(Pull, "#theta"), PAIR(DeltaPull, "#Delta #theta"), PAIR(Dipolarity, "D"), PAIR(DeltaHt, "#Delta H_{T}"), PAIR(Mass12), PAIR(Mass23), PAIR(Mass13), PAIR(Pt12), PAIR(Pt23), PAIR(Pt13), PAIR(DeltaPt23), PAIR(DeltaPt13), PAIR(Ht12), PAIR(Ht23), PAIR(Ht13), PAIR(Rho23), PAIR(Rho13), PAIR(DeltaRap23), PAIR(DeltaRap13), PAIR(DeltaPhi23), PAIR(DeltaPhi13), PAIR(DeltaR23), PAIR(DeltaR13), PAIR(DeltaM23), PAIR(DeltaM13), PAIR(DeltaHt23), PAIR(DeltaHt13), PAIR(Pull23), PAIR(Pull13), PAIR(DeltaPull13), PAIR(Dipolarity23), PAIR(Dipolarity13), PAIR(Aplanarity), PAIR(Sphericity)}
);
}

SignatureLeptonicBranch::SignatureLeptonicBranch()
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

OctetBranch::OctetBranch()
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

EventBranch::EventBranch() {}

TopLeptonicPairBranch::TopLeptonicPairBranch() {}

TripletPairBranch::TripletPairBranch()
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

QuartetPairBranch::QuartetPairBranch()
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
Observables SignatureLeptonicBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(HardTopPt), PAIR(SoftTopPt), PAIR(HiggsMass), PAIR(PairRap), PAIR(Aplanarity), PAIR(Sphericity)});
}
Observables TripletPairBranch::Variables() const
{
    return Join(PairBranch::Variables(), {PAIR(BottomPt), PAIR(BottomRap), PAIR(BottomPhi), PAIR(BottomMass), PAIR(TopPt), PAIR(TopRap), PAIR(TopPhi), PAIR(TopMass), PAIR(TopBdt)});
}
Observables EventBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(JetNumber), PAIR(BottomNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
}
Observables EventBranch::Spectators() const
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber)});
}
}
}

