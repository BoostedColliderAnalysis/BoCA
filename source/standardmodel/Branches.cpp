/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/Branches.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace standardmodel
{

BottomBase::BottomBase()
{
    VertexMass = InValue();
    MaxDisplacement = InValue();
    MeanDisplacement = InValue();
    SumDisplacement = InValue();
    Multiplicity = static_cast<int>(InValue());
    Radius = InValue();
    Spread = InValue();
    VertexRadius = InValue();
    VertexSpread = InValue();
    EnergyFraction = InValue();
    EnergyRatio = InValue();
    MomentumRatio = InValue();
}

Observables BottomBase::Variables()
{
    return OBSERVABLE(VertexMass, latex::String("m_{V}") + " [GeV]") + OBSERVABLE(MaxDisplacement, "log(" + latex::String("\\Delta d") + "_{max} / mm)") + OBSERVABLE(MeanDisplacement, "log(" + latex::String("\\Delta d") + "_{mean} / mm)") + OBSERVABLE(SumDisplacement, "log(" + latex::String("\\Delta d") + "_{sum} / mm)") + OBSERVABLE(Multiplicity, latex::String("n_{V}")) + OBSERVABLE(Radius, latex::String("r")) + OBSERVABLE(Spread, latex::String("s")) + OBSERVABLE(VertexRadius, latex::String("r_{V}")) + OBSERVABLE(VertexSpread, latex::String("s_{V}")) + OBSERVABLE(EnergyFraction, latex::String("f_{E}"))
//     + OBSERVABLE(EnergyRatio, latex::String("r_{E}")) + OBSERVABLE(MomentumRatio, latex::String("r_{p}"))
    ;
}

Observables BottomBase::Spectators()
{
    return {};
}

float BottomBase::InValue()
{
    return BaseBranch::InitialValue();
}

Observables BottomBranch::Variables()
{
    return ParticleBranch::Variables() + BottomBase::Variables();
}

Observables BottomBranch::Spectators()
{
    return ParticleBranch::Spectators() + BottomBase::Variables();
}

TauBranch::TauBranch()
{
    EmRadius = InitialValue();
    TrackRadius = InitialValue();
    MomentumFraction = InitialValue();
    CoreEnergyFraction = InitialValue();
    EmFraction = InitialValue();
    ClusterMass = InitialValue();
    TrackMass = InitialValue();
    FlightPath = InitialValue();
    TrtHtFraction = InitialValue();
}

Observables TauBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(EmRadius) + OBSERVABLE(TrackRadius) + OBSERVABLE(MomentumFraction) + OBSERVABLE(CoreEnergyFraction) + OBSERVABLE(EmFraction) + OBSERVABLE(ClusterMass) + OBSERVABLE(TrackMass) + OBSERVABLE(FlightPath) + OBSERVABLE(TrtHtFraction);
}

Observables TauBranch::Spectators()
{
    return ParticleBranch::Spectators();
}

Observables WHadronicBranch::Variables()
{
    return PairBranch::Variables() + BottomBase::Variables();
}

Observables WHadronicBranch::Spectators()
{
    return PairBranch::Spectators() + BottomBase::Spectators();
}

Observables ZHadronicBranch::Variables()
{
    return PairBranch::Variables() + BottomBase::Variables();
}

Observables ZHadronicBranch::Spectators()
{
    return PairBranch::Spectators() + BottomBase::Spectators();
}

WLeptonicBranch::WLeptonicBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables WLeptonicBranch::Variables()
{
    return ResultBranch::Variables() + OBSERVABLE(Pt, latex::String("p_T") + " [GeV]") + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
}

TopHadronicBranch::TopHadronicBranch()
{
    BottomMass = InitialValue();
    WMass = InitialValue();
    LeptonPt = InitialValue();
    LeptonDeltaR = InitialValue();
}

Observables TopHadronicBranch::Variables()
{
    return MultiBranch::Variables() + BottomBase::Variables() /*+ OBSERVABLE(LeptonPt) + OBSERVABLE(LeptonDeltaR)*/ + OBSERVABLE(WMass) + OBSERVABLE(BottomMass);
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + latex::String("_{W}")) + OBSERVABLE(Bdt2, "BDT" + latex::String("_{b}")) + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // everything
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]"); // masses
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // bottom
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]"); // just mass
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + latex::String("_{W}")) + OBSERVABLE(Bdt2, "BDT" + latex::String("_{b}")) + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]"); // kinematics + bdts
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + latex::String("_{W}")); // mass and W bdt
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + latex::String("_{W}")) + OBSERVABLE(Bdt2, "BDT" + latex::String("_{b}")); // mass and bdt
    return MultiBranch::Variables() + BottomBase::Variables(); // FIXME usually we use the lepton pt
}

Observables TopHadronicBranch::Spectators()
{
    return MultiBranch::Spectators() + BottomBase::Spectators();
}

TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonicBranch::Variables()
{
    return BottomBase::Variables() + ParticleBranch::Variables() + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaM) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(Bdt2) + OBSERVABLE(BottomPt) + OBSERVABLE(LeptonPt) + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/ + OBSERVABLE(Bdt1);
}

Observables TopLeptonicBranch::Spectators()
{
    return PairBranch::Spectators() + BottomBase::Spectators();
}

HiggsBranch::HiggsBranch()
{
    LeptonPt = InitialValue();
    LeptonDeltaR = InitialValue();
}

Observables HiggsBranch::Variables()
{
//   return {OBSERVABLE(Mass) + OBSERVABLE(Bdt1) + OBSERVABLE(Bdt2)};
    return PairBranch::Variables() + BottomBase::Variables() + OBSERVABLE(LeptonPt) + OBSERVABLE(LeptonDeltaR);
}

Observables HiggsBranch::Spectators()
{
    return PairBranch::Spectators() + BottomBase::Spectators();
}


TopHadronicHepBranch::TopHadronicHepBranch()
{
    LeptonPt = InitialValue();
    BottomMass = InitialValue();
    WMass = InitialValue();
}

Observables TopHadronicHepBranch::Variables()
{
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]"); // masses
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, latex::String("m") + " [GeV]"); // just mass
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // bottom info
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(BottomMass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(WMass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}"))/* + OBSERVABLE(Dipolarity, latex::String("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(Pt, latex::String("p_T") + " [GeV]") + OBSERVABLE(Ht, latex::String("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/;
    return OBSERVABLE(LeptonPt) + OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(Pt, latex::String("p_T") + " [GeV]") + OBSERVABLE(Ht, latex::String("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(Bdt1, "BDT" + latex::String("_{W}")) + OBSERVABLE(Bdt2, "BDT" + latex::String("_{b}")) + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/;
}

Observables TopHadronicHepBranch::Spectators()
{
    return MultiBranch::Spectators() + BottomBase::Spectators();
}

TruthBranch::TruthBranch()
{
    TopPt = InitialValue();
    BottomPt = InitialValue();
    WPt = InitialValue();
    Quark1Pt = InitialValue();
    Quark2Pt = InitialValue();
    DeltaRTop = InitialValue();
    DeltaRW = InitialValue();
    RhoTop = InitialValue();
    RhoW = InitialValue();
}

}

}
