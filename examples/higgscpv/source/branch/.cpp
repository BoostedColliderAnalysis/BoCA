#include "boca/esHiggsCpv.hh"
#include "boca/OBSERVABLE.hh"

namespace higgscpv
{

namespace branch
{

SignatureTTagger::SignatureTTagger()
{
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureTTagger::Variables()
{
    return OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity) + ThreeBody::Variables();
}

Observables SignatureLeptonTTagger::Variables()
{
//     return OBSERVABLE(Ht, "H_{T}") + OBSERVABLE(DeltaPt, "\\Delta P_{T}") + OBSERVABLE(DeltaM, "\\Delta m") + OBSERVABLE(DeltaRap, "\\Delta \\eta") + OBSERVABLE(DeltaPhi, "\\Delta \\phi") + OBSERVABLE(DeltaR, "\\Delta R") + OBSERVABLE(Rho, "\\rho") + OBSERVABLE(DeltaHt, "\\Delta H_{T}") + OBSERVABLE(Bdt3) + OBSERVABLE(Mass12) + OBSERVABLE(Mass23) + OBSERVABLE(Mass13) + OBSERVABLE(Pt12) + OBSERVABLE(Pt23) + OBSERVABLE(Pt13) + OBSERVABLE(DeltaPt23) + OBSERVABLE(DeltaPt13) + OBSERVABLE(Ht12) + OBSERVABLE(Ht23) + OBSERVABLE(Ht13) + OBSERVABLE(Rho23) + OBSERVABLE(Rho13) + OBSERVABLE(DeltaRap23) + OBSERVABLE(DeltaRap13) + OBSERVABLE(DeltaPhi23) + OBSERVABLE(DeltaPhi13) + OBSERVABLE(DeltaR23) + OBSERVABLE(DeltaR13) + OBSERVABLE(DeltaM23) + OBSERVABLE(DeltaM13) + OBSERVABLE(DeltaHt23) + OBSERVABLE(DeltaHt13) + OBSERVABLE(Pull23) + OBSERVABLE(Pull13) + OBSERVABLE(Pull32) + OBSERVABLE(Pull31) /*+ OBSERVABLE(Dipolarity23) + OBSERVABLE(Dipolarity13)*/ + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity);
  return SignatureTTagger::Variables();
}



SignatureLeptonTagger::SignatureLeptonTagger()
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
//     Dipolarity23 = InitialValue();
//     Dipolarity13 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureLeptonTagger::Variables()
{
    return branch::Multi::Variables() + OBSERVABLE(Mass12) + OBSERVABLE(Mass23) + OBSERVABLE(Mass13) + OBSERVABLE(Pt12) + OBSERVABLE(Pt23) + OBSERVABLE(Pt13) + OBSERVABLE(DeltaPt23) + OBSERVABLE(DeltaPt13) + OBSERVABLE(Ht12) + OBSERVABLE(Ht23) + OBSERVABLE(Ht13) + OBSERVABLE(Rho23) + OBSERVABLE(Rho13) + OBSERVABLE(DeltaRap23) + OBSERVABLE(DeltaRap13) + OBSERVABLE(DeltaPhi23) + OBSERVABLE(DeltaPhi13) + OBSERVABLE(DeltaR23) + OBSERVABLE(DeltaR13) + OBSERVABLE(DeltaM23) + OBSERVABLE(DeltaM13) + OBSERVABLE(DeltaHt23) + OBSERVABLE(DeltaHt13) + OBSERVABLE(Pull23) + OBSERVABLE(Pull13) + OBSERVABLE(DeltaPull13) +/* OBSERVABLE(Dipolarity23) + OBSERVABLE(Dipolarity13) +*/ OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity);
}

SignatureLeptonic::SignatureLeptonic()
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

Octet::Octet()
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

Event::Event() {}

TopLeptonicTwoBody::TopLeptonicTwoBody() {}

TripletTwoBody::TripletTwoBody()
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

QuartetTwoBody::QuartetTwoBody()
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
Observables SignatureLeptonic::Variables()
{
    return Multi::Variables() + OBSERVABLE(BottomBdt) + OBSERVABLE(PairBottomBdt) + OBSERVABLE(HardTopPt) + OBSERVABLE(SoftTopPt) + OBSERVABLE(HiggsMass) + OBSERVABLE(PairRap) + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity);
}

Observables TripletTwoBody::Variables()
{
    return TwoBody::Variables() + OBSERVABLE(BottomPt) + OBSERVABLE(BottomRap) + OBSERVABLE(BottomPhi) + OBSERVABLE(BottomMass) + OBSERVABLE(TopPt) + OBSERVABLE(TopRap) + OBSERVABLE(TopPhi) + OBSERVABLE(TopMass) + OBSERVABLE(TopBdt);
}

Observables Event::Variables()
{
    return Event::Variables();
}

Observables Event::Spectators()
{
  return Event::Spectators();
}
}
}

