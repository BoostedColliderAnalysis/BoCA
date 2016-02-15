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
    return boca::TChannelBranch::Variables() + OBSERVABLE(VetoBdt);
}

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
    VetoBdt = InitialValue();
    TopPt = InitialValue();
    HiggsPt = InitialValue();
}

Observables SignatureSingleHadronicBranch::Variables()
{
    return boca::TChannelBranch::Variables() + OBSERVABLE(VetoBdt) + OBSERVABLE(TopPt) + OBSERVABLE(HiggsPt);
}

Observables EventBranch::Variables()
{
    return MultiBranch::Variables() + OBSERVABLE(LeptonNumber) + OBSERVABLE(BottomNumber) + OBSERVABLE(JetNumber) + OBSERVABLE(MissingEt) + OBSERVABLE(ScalarHt) + OBSERVABLE(LeptonHt) + OBSERVABLE(JetMass) + OBSERVABLE(JetPt) + OBSERVABLE(JetHt) + OBSERVABLE(JetRap) + OBSERVABLE(JetPhi);
}

}

}
