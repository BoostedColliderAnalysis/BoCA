/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/Branches.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace standardmodel
{

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
    return ResultBranch::Variables() + OBSERVABLE(Pt, Latex("p_T") + " [GeV]") + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
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
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Latex("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Latex("_{b}")) + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/; // everything
    return OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]"); // masses
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/; // bottom
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, Latex("m") + " [GeV]"); // just mass
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Latex("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Latex("_{b}")) + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]"); // kinematics + bdts
    return OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Latex("_{W}")); // mass and W bdt
    return OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Latex("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Latex("_{b}")); // mass and bdt
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
    return BottomBase::Variables() + ParticleBranch::Variables() + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaM) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(Bdt2) + OBSERVABLE(BottomPt) + OBSERVABLE(LeptonPt) + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/ + OBSERVABLE(Bdt1);
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
    return OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]"); // masses
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, Latex("m") + " [GeV]"); // just mass
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/; // bottom info
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(BottomMass, Latex("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Latex("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}"))/* + OBSERVABLE(Dipolarity, Latex("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(Pt, Latex("p_T") + " [GeV]") + OBSERVABLE(Ht, Latex("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/;
    return OBSERVABLE(LeptonPt) + OBSERVABLE(DeltaHt, Latex("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Latex("m") + " [GeV]") + OBSERVABLE(Pt, Latex("p_T") + " [GeV]") + OBSERVABLE(Ht, Latex("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Latex("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Latex("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Latex("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Latex("\\Delta \\phi")) + OBSERVABLE(DeltaR, Latex("\\Delta R")) + OBSERVABLE(Rho, Latex("\\rho")) + OBSERVABLE(Bdt1, "BDT" + Latex("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Latex("_{b}")) + OBSERVABLE(Pull1, Latex("#theta_{1}")) + OBSERVABLE(Pull2, Latex("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Latex("D"))*/;
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
