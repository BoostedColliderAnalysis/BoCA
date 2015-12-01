/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BranchesSm.hh"
#include "Pair.hh"

namespace boca {

namespace standardmodel {

Observables BottomBranch::Variables()
{
    return Join(ParticleBranch::Variables(), BottomBase::Variables());
}

Observables BottomBranch::Spectators()
{
    return Join(ParticleBranch::Spectators(), BottomBase::Variables());
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
    return Join(ParticleBranch::Variables(), {PAIR(EmRadius), PAIR(TrackRadius), PAIR(MomentumFraction), PAIR(CoreEnergyFraction), PAIR(EmFraction), PAIR(ClusterMass), PAIR(TrackMass), PAIR(FlightPath), PAIR(TrtHtFraction)});
}

Observables TauBranch::Spectators()
{
    return ParticleBranch::Spectators();
}

Observables WHadronicBranch::Variables()
{
  return Join(PairBranch::Variables(), BottomBase::Variables());
}

Observables WHadronicBranch::Spectators()
{
  return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

Observables ZHadronicBranch::Variables()
{
  return Join(PairBranch::Variables(), BottomBase::Variables());
}

Observables ZHadronicBranch::Spectators()
{
  return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

WSemiBranch::WSemiBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables WSemiBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(LeptonPt), PAIR(NeutrinoPt)});
}

TopHadronicBranch::TopHadronicBranch()
{
//   std::cout << "we are here\n";
//     BottomMass = InitialValue();
//     WMass = InitialValue();
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
    return Join(MultiBranch::Variables(), BottomBase::Variables(), {PAIR(LeptonPt)});
}

Observables TopHadronicBranch::Spectators()
{
    return Join(MultiBranch::Spectators(), BottomBase::Spectators());
}

TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonicBranch::Variables()
{
  return  Join(BottomBase::Variables(), ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(Bdt2), PAIR(BottomPt), PAIR(LeptonPt), PAIR(Pull2,"#theta"), PAIR(Dipolarity,"D")});
}

Observables TopLeptonicBranch::Spectators()
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

HiggsBranch::HiggsBranch(){
  LeptonPt = InitialValue();
  LeptonDeltaR = InitialValue();
}

Observables HiggsBranch::Variables()
{
//   return {PAIR(Mass), PAIR(Bdt1), PAIR(Bdt2)};
  return Join(PairBranch::Variables(), BottomBase::Variables(),{PAIR(LeptonPt),PAIR(LeptonDeltaR)});
}

Observables HiggsBranch::Spectators()
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

}

}
