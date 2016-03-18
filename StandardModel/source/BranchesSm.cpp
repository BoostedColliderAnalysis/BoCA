/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "BranchesSm.hh"
#include "OBSERVABLE.hh"
#include "plotting/Font.hh"

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
    return ResultBranch::Variables() + OBSERVABLE(Pt, Formula("p_T") + " [GeV]") + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
}

TopHadronicBranch::TopHadronicBranch()
{
    BottomMass = InitialValue();
    WMass = InitialValue();
    LeptonPt = InitialValue();
//     Tau1_1 = InitialValue();
//     Tau2_1 = InitialValue();
//     Tau3_1 = InitialValue();
//     Tau21_1 = InitialValue();
//     Tau32_1 = InitialValue();
//     Tau1_2 = InitialValue();
//     Tau2_2 = InitialValue();
//     Tau3_2 = InitialValue();
//     Tau21_2 = InitialValue();
//     Tau32_2 = InitialValue();
}

Observables TopHadronicBranch::Variables()
{
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Formula("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Formula("_{b}")) + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/; // everything
    return OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]"); // masses
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/; // bottom
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, Formula("m") + " [GeV]"); // just mass
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Formula("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Formula("_{b}")) + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]"); // kinematics + bdts
    return OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Formula("_{W}")); // mass and W bdt
    return OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(Bdt1, "BDT" + Formula("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Formula("_{b}")); // mass and bdt
    return MultiBranch::Variables() + BottomBase::Variables() +  Observables(OBSERVABLE(LeptonPt));
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
    Observables observables = BottomBase::Variables() + ParticleBranch::Variables() + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaM) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho) + OBSERVABLE(Bdt2) + OBSERVABLE(BottomPt) + OBSERVABLE(LeptonPt) + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/ + OBSERVABLE(Bdt1);
    return observables;
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
    return OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]"); // masses
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(Mass, Formula("m") + " [GeV]"); // just mass
    return BottomBase::Variables() + OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/; // bottom info
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(BottomMass, Formula("m_{b}") + " [GeV]") + OBSERVABLE(WMass, Formula("m_{W}") + " [GeV]") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}"))/* + OBSERVABLE(Dipolarity, Formula("D"))*/; // subjet info
    return OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(Pt, Formula("p_T") + " [GeV]") + OBSERVABLE(Ht, Formula("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/;
    return OBSERVABLE(LeptonPt) + OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(Pt, Formula("p_T") + " [GeV]") + OBSERVABLE(Ht, Formula("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(Bdt1, "BDT" + Formula("_{W}")) + OBSERVABLE(Bdt2, "BDT" + Formula("_{b}")) + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/;
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
