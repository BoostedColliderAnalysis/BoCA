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
    veto_bdt = InitialValue();
}

Observables SignatureSingleBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}");
}

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
    veto_bdt = InitialValue();
    top_pt = InitialValue();
    higgs_pt = InitialValue();
}

Observables SignatureSingleHadronicBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}") + OBSERVABLE(top_pt, "p_{T}(t)") + OBSERVABLE(higgs_pt, "p_{T}(h)") + EventShapesBase::Variables();
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
    top_pt = InitialValue();
    lepton_pt = InitialValue();
    softest_boson_pt = InitialValue();
    hardest_boson_pt = InitialValue();
    boson_number = static_cast<int>(InitialValue());
    hard_boson_number = static_cast<int>(InitialValue());
    detectable_boson_number = static_cast<int>(InitialValue());
    boson_delta_r_min = InitialValue();
    missing_et = InitialValue();
    scalar_ht = InitialValue();
    jet_pt = InitialValue();
}

Observables Truth::Variables()
{
    return OBSERVABLE(top_pt, "p_{T}(t)") + OBSERVABLE(lepton_pt, "p_{T}(l)") + OBSERVABLE(hard_boson_number, "#B^{0}_{hard}") + OBSERVABLE(softest_boson_pt, "p_{T}(B^{0})_{soft}") + OBSERVABLE(detectable_boson_number, "#B^{0}_{detect}") + OBSERVABLE(hardest_boson_pt, "p_{T}(B)_{hard}") + OBSERVABLE(boson_delta_r_min, "\\Delta R(B,B)_{min}") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}") + OBSERVABLE(jet_pt, "p_{T}(j)");
}

NewEvent::NewEvent()
{
    global_bdt = InitialValue();
    signature_bdt = InitialValue();
}

Observables NewEvent::Variables()
{
    return Bdt::Variables() + OBSERVABLE(global_bdt, "BDT_{global}") + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

NewEvent2::NewEvent2()
{
    veto_bdt = InitialValue();
    signature_bdt = InitialValue();
}

Observables NewEvent2::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(veto_bdt, "BDT_{veto}") + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

Observables NewEvent2::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

NewEvent3::NewEvent3()
{
    signature_bdt = InitialValue();
}

Observables NewEvent3::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

Observables NewEvent3::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

NewEvent4::NewEvent4()
{
    signature_bdt = InitialValue();
}

Observables NewEvent4::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + EventShapesBase::Variables() + OBSERVABLE(signature_bdt, "BDT_{Signature}");
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
