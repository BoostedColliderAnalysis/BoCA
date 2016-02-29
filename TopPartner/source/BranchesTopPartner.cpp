/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "BranchesTopPartner.hh"
#include "OBSERVABLE.hh"

namespace boca
{

namespace naturalness
{

SignatureSingleBranch::SignatureSingleBranch()
{
    VetoBdt = InitialValue();
}

Observables SignatureSingleBranch::Variables()
{
    return SignatureBranch::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}");
}

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
    VetoBdt = InitialValue();
    TopPt = InitialValue();
    HiggsPt = InitialValue();
}

Observables SignatureSingleHadronicBranch::Variables()
{
    return SignatureBranch::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}") + OBSERVABLE(TopPt, "p_{T}^{t}") + OBSERVABLE(HiggsPt, "p_{T}^{h}");
}

TruthBranch::TruthBranch()
{
    TopPt = InitialValue();
    LeptonPt = InitialValue();
    SoftestBosonPt = InitialValue();
    HardestBosonPt = InitialValue();
    BosonNumber = int(InitialValue());
    HardBosonNumber = int(InitialValue());
    DetectableBosonNumber = int(InitialValue());
    BosonDeltaRMin = InitialValue();
}

Observables TruthBranch::Variables()
{
    return OBSERVABLE(TopPt) + OBSERVABLE(LeptonPt) + OBSERVABLE(HardBosonNumber) + OBSERVABLE(SoftestBosonPt) + OBSERVABLE(DetectableBosonNumber) + OBSERVABLE(HardestBosonPt) + OBSERVABLE(BosonDeltaRMin);
}

NewEventBranch::NewEventBranch()
{
  GlobBdt = InitialValue();
  JetMass = InitialValue();
  JetPt = InitialValue();
  JetHt = InitialValue();
  JetRap = InitialValue();
  JetPhi = InitialValue();
}

Observables NewEventBranch::Variables()
{
  return MultiBranch::Variables() + OBSERVABLE(GlobBdt, "BDT_{global}") + OBSERVABLE(JetMass, "m_{j}") + OBSERVABLE(JetPt, "p_{T}^{j}") + OBSERVABLE(JetHt, "H_{T}^{j}") + OBSERVABLE(JetRap, "#eta_{j}") + OBSERVABLE(JetPhi, "#phi_{j}");
}

}

}
