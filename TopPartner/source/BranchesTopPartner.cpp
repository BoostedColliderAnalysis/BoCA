/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/BranchesTopPartner.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace naturalness
{

Observables VetoTopPartnerBranch::Variables()
{
    return MultiBranch::Variables() + EventShapesBase::Variables();
}

Observables VetoTopPartnerBranch::Spectators()
{
    return MultiBranch::Spectators() + EventShapesBase::Spectators();
}

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
    return SignatureBranch::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}") + OBSERVABLE(TopPt, "p_{T}(t)") + OBSERVABLE(HiggsPt, "p_{T}(h)") + EventShapesBase::Variables();
}

Observables SignatureSingleHadronicBranch::Spectators()
{
    return SignatureBranch::Spectators() + EventShapesBase::Spectators();
}

SignatureEffectiveBranch::SignatureEffectiveBranch()
{
}

Observables SignatureEffectiveBranch::Variables()
{
    return SignatureBranch::Variables() + EventShapesBase::Variables();
}

Observables SignatureEffectiveBranch::Spectators()
{
    return SignatureBranch::Spectators() + EventShapesBase::Spectators();
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
    MissingEt = InitialValue();
    ScalarHt = InitialValue();
    JetPt = InitialValue();
}

Observables TruthBranch::Variables()
{
    return OBSERVABLE(TopPt, "p_{T}(t)") + OBSERVABLE(LeptonPt, "p_{T}(l)") + OBSERVABLE(HardBosonNumber, "#B^{0}_{hard}") + OBSERVABLE(SoftestBosonPt, "p_{T}(B^{0})_{soft}") + OBSERVABLE(DetectableBosonNumber, "#B^{0}_{detect}") + OBSERVABLE(HardestBosonPt, "p_{T}(B)_{hard}") + OBSERVABLE(BosonDeltaRMin, "\\Delta R(B,B)_{min}") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}") + OBSERVABLE(JetPt, "p_{T}(j)");
}

NewEventBranch::NewEventBranch()
{
    GlobalBdt = InitialValue();
    SignatureBdt = InitialValue();
}

Observables NewEventBranch::Variables()
{
    return BdtBranch::Variables() + OBSERVABLE(GlobalBdt, "BDT_{global}") + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

NewEventBranch2::NewEventBranch2()
{
    VetoBdt = InitialValue();
    SignatureBdt = InitialValue();
}

Observables NewEventBranch2::Variables()
{
    return BdtBranch::Variables() + GlobalBase::Variables() + OBSERVABLE(VetoBdt, "BDT_{veto}") + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEventBranch2::Spectators()
{
    return BdtBranch::Spectators() + GlobalBase::Spectators();
}

NewEventBranch3::NewEventBranch3()
{
    SignatureBdt = InitialValue();
}

Observables NewEventBranch3::Variables()
{
    return BdtBranch::Variables() + GlobalBase::Variables() + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEventBranch3::Spectators()
{
    return BdtBranch::Spectators() + GlobalBase::Spectators();
}

NewEventBranch4::NewEventBranch4(){
  SignatureBdt = InitialValue();
}

Observables NewEventBranch4::Variables()
{
  return BdtBranch::Variables() + GlobalBase::Variables() + EventShapesBase::Variables() + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEventBranch4::Spectators()
{
  return BdtBranch::Spectators() + GlobalBase::Spectators() + EventShapesBase::Spectators();
}

CompleteBranch::CompleteBranch()
{
}

Observables CompleteBranch::Variables()
{
    return SignatureSingleHadronicBranch::Variables() + GlobalBase::Variables();
}

Observables CompleteBranch::Spectators()
{
    return SignatureSingleHadronicBranch::Spectators() + GlobalBase::Spectators();
}

}

}
