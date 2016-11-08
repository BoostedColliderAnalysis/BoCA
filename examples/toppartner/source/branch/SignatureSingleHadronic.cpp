/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/branch/SignatureSingleHadronic.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace toppartner
{


namespace branch
{

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
    veto_bdt = InitialValue();
    top_pt = InitialValue();
    higgs_pt = InitialValue();
}

boca::Observables SignatureSingleHadronicBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}") + OBSERVABLE(top_pt, "p_{T}(t)") + OBSERVABLE(higgs_pt, "p_{T}(h)") + EventShapesBase::Variables();
}

boca::Observables SignatureSingleHadronicBranch::Spectators()
{
    return ThreeBody::Spectators() + EventShapesBase::Spectators();
}

}

}
