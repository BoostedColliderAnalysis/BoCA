/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "BranchesTopPartner.hh"
#include "plotting/Font.hh"
#include "OBSERVABLE.hh"

namespace boca
{

namespace naturalness
{

Observables VetoTopPartnerBranch::Variables()
{
    return MultiBranch::Variables() + EventShapesBranch::Variables();
}

Observables VetoTopPartnerBranch::Spectators()
{
    return MultiBranch::Spectators() + EventShapesBranch::Spectators();
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
    return SignatureBranch::Variables() + OBSERVABLE(VetoBdt, "BDT_{V}") + OBSERVABLE(TopPt, "p_{T}(t)") + OBSERVABLE(HiggsPt, "p_{T}(h)") + EventShapesBranch::Variables();
}

Observables SignatureSingleHadronicBranch::Spectators()
{
    return SignatureBranch::Spectators() + EventShapesBranch::Spectators();
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
    return OBSERVABLE(TopPt, Formula("p_{T}(t)")) + OBSERVABLE(LeptonPt, Formula("p_{T}(l)")) + OBSERVABLE(HardBosonNumber, Formula("#B^{0}") + "_{hard}") + OBSERVABLE(SoftestBosonPt, Formula("p_{T}(B^{0})") + "_{soft}") + OBSERVABLE(DetectableBosonNumber, Formula("#B^{0}") + "_{detect}") + OBSERVABLE(HardestBosonPt, Formula("p_{T}(B)") + "_{hard}") + OBSERVABLE(BosonDeltaRMin, Formula("\\Delta R(B,B)") + "_{min}") + OBSERVABLE(MissingEt, Formula("E_{T}") + "^{miss}") + OBSERVABLE(ScalarHt, Formula("H_{T}")) + OBSERVABLE(JetPt, Formula("p_{T}(j)"));
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
