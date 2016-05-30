/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/BranchesTopPartner.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace toppartner
{

Observables VetoTopPartnerBranch::Variables()
{
    return Multi::Variables() + EventShapesBase::Variables();
}

Observables VetoTopPartnerBranch::Spectators()
{
    return Multi::Spectators() + EventShapesBase::Spectators();
}

SignatureSingleBranch::SignatureSingleBranch()
{
    VetoBdt = InitialValue();
}

Observables SignatureSingleBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}");
}

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
    VetoBdt = InitialValue();
    TopPt = InitialValue();
    HiggsPt = InitialValue();
}

Observables SignatureSingleHadronicBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}") + OBSERVABLE(TopPt, "p_{T}(t)") + OBSERVABLE(HiggsPt, "p_{T}(h)") + EventShapesBase::Variables();
}

Observables SignatureSingleHadronicBranch::Spectators()
{
    return ThreeBody::Spectators() + EventShapesBase::Spectators();
}

SignatureEffectiveBranch::SignatureEffectiveBranch()
{
}

Observables SignatureEffectiveBranch::Variables()
{
    return ThreeBody::Variables() + EventShapesBase::Variables();
}

Observables SignatureEffectiveBranch::Spectators()
{
    return ThreeBody::Spectators() + EventShapesBase::Spectators();
}

Truth::Truth()
{
    TopPt = InitialValue();
    LeptonPt = InitialValue();
    SoftestBosonPt = InitialValue();
    HardestBosonPt = InitialValue();
    BosonNumber = static_cast<int>(InitialValue());
    HardBosonNumber = static_cast<int>(InitialValue());
    DetectableBosonNumber = static_cast<int>(InitialValue());
    BosonDeltaRMin = InitialValue();
    MissingEt = InitialValue();
    ScalarHt = InitialValue();
    JetPt = InitialValue();
}

Observables Truth::Variables()
{
    return OBSERVABLE(TopPt, "p_{T}(t)") + OBSERVABLE(LeptonPt, "p_{T}(l)") + OBSERVABLE(HardBosonNumber, "#B^{0}_{hard}") + OBSERVABLE(SoftestBosonPt, "p_{T}(B^{0})_{soft}") + OBSERVABLE(DetectableBosonNumber, "#B^{0}_{detect}") + OBSERVABLE(HardestBosonPt, "p_{T}(B)_{hard}") + OBSERVABLE(BosonDeltaRMin, "\\Delta R(B,B)_{min}") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}") + OBSERVABLE(JetPt, "p_{T}(j)");
}

NewEvent::NewEvent()
{
    GlobalBdt = InitialValue();
    SignatureBdt = InitialValue();
}

Observables NewEvent::Variables()
{
    return Bdt::Variables() + OBSERVABLE(GlobalBdt, "BDT_{global}") + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

NewEvent2::NewEvent2()
{
    VetoBdt = InitialValue();
    SignatureBdt = InitialValue();
}

Observables NewEvent2::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(VetoBdt, "BDT_{veto}") + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEvent2::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

NewEvent3::NewEvent3()
{
    SignatureBdt = InitialValue();
}

Observables NewEvent3::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEvent3::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

NewEvent4::NewEvent4(){
  SignatureBdt = InitialValue();
}

Observables NewEvent4::Variables()
{
  return Bdt::Variables() + GlobalBase::Variables() + EventShapesBase::Variables() + OBSERVABLE(SignatureBdt, "BDT_{Signature}");
}

Observables NewEvent4::Spectators()
{
  return Bdt::Spectators() + GlobalBase::Spectators() + EventShapesBase::Spectators();
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
