/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BranchesSm.hh"
#include "Pair.hh"
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
    return ParticleBranch::Variables() + PAIR(EmRadius) + PAIR(TrackRadius) + PAIR(MomentumFraction) + PAIR(CoreEnergyFraction) + PAIR(EmFraction) + PAIR(ClusterMass) + PAIR(TrackMass) + PAIR(FlightPath) + PAIR(TrtHtFraction);
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
    return ResultBranch::Variables() + PAIR(Pt, Formula("p_T") + " [GeV]") + PAIR(Ht) + PAIR(DeltaPt) + PAIR(DeltaRap) + PAIR(DeltaPhi) + PAIR(DeltaR) + PAIR(Rho) + PAIR(LeptonPt) + PAIR(NeutrinoPt);
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
    return BottomBase::Variables() + PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Bdt1, "BDT" + Formula("_{W}")) + PAIR(Bdt2, "BDT" + Formula("_{b}")) + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]") + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D")); // everything
    return PAIR(Mass, Formula("m") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]"); // masses
    return BottomBase::Variables() + PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]") + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D")); // bottom
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]"); // kinematics
    return PAIR(Mass, Formula("m") + " [GeV]"); // just mass
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]") + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D")); // subjet info
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Bdt1, "BDT" + Formula("_{W}")) + PAIR(Bdt2, "BDT" + Formula("_{b}")) + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]"); // kinematics + bdts
    return PAIR(Mass, Formula("m") + " [GeV]") + PAIR(Bdt1, "BDT" + Formula("_{W}")); // mass and W bdt
    return PAIR(Mass, Formula("m") + " [GeV]") + PAIR(Bdt1, "BDT" + Formula("_{W}")) + PAIR(Bdt2, "BDT" + Formula("_{b}")); // mass and bdt
    return MultiBranch::Variables() + BottomBase::Variables() +  Observables(PAIR(LeptonPt));
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
    Observables observables = BottomBase::Variables() + ParticleBranch::Variables() + PAIR(Ht) + PAIR(DeltaPt) + PAIR(DeltaM) + PAIR(DeltaRap) + PAIR(DeltaPhi) + PAIR(DeltaR) + PAIR(Rho) + PAIR(Bdt2) + PAIR(BottomPt) + PAIR(LeptonPt) + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta")) + PAIR(Dipolarity, Formula("D")) + PAIR(Bdt1);
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
//   return {PAIR(Mass) + PAIR(Bdt1) + PAIR(Bdt2)};
    return PairBranch::Variables() + BottomBase::Variables() + PAIR(LeptonPt) + PAIR(LeptonDeltaR);
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
    return PAIR(Mass, Formula("m") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]"); // masses
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]"); // kinematics
    return PAIR(Mass, Formula("m") + " [GeV]"); // just mass
    return BottomBase::Variables() + PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]") + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D")); // bottom info
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(BottomMass, Formula("m_{b}") + " [GeV]") + PAIR(WMass, Formula("m_{W}") + " [GeV]") + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D")); // subjet info
    return PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(Pt, Formula("p_T") + " [GeV]") + PAIR(Ht, Formula("H_{T}") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D"));
    return PAIR(LeptonPt) + PAIR(DeltaHt, Formula("#Delta H_{T}") + " [GeV]") + PAIR(Mass, Formula("m") + " [GeV]") + PAIR(Pt, Formula("p_T") + " [GeV]") + PAIR(Ht, Formula("H_{T}") + " [GeV]") + PAIR(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + PAIR(DeltaM, Formula("#Delta m") + " [GeV]") + PAIR(DeltaRap, Formula("#Delta #eta")) + PAIR(DeltaPhi, Formula("#Delta #phi")) + PAIR(DeltaR, Formula("#Delta R")) + PAIR(Rho, Formula("#rho")) + PAIR(Bdt1, "BDT" + Formula("_{W}")) + PAIR(Bdt2, "BDT" + Formula("_{b}")) + PAIR(Pull1, Formula("#theta_{1}")) + PAIR(Pull2, Formula("#theta_{2}")) + PAIR(Dipolarity, Formula("D"));
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
