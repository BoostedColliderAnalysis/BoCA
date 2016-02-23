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

Observables EventBranch::Variables()
{
    return MultiBranch::Variables() + OBSERVABLE(LeptonNumber, "##l") + OBSERVABLE(BottomNumber, "##b") + OBSERVABLE(JetNumber, "##j") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}^{scalar}") + OBSERVABLE(LeptonHt, "H_{T}^{l}") + OBSERVABLE(JetMass, "m_{j}") + OBSERVABLE(JetPt, "p_{T}^{j}") + OBSERVABLE(JetHt, "H_{T}^{j}") + OBSERVABLE(JetRap, "#eta_{j}") + OBSERVABLE(JetPhi, "#phi_{j}");
}

}

}
