/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/SignatureSingle.hh"
#include "boca/OBSERVABLE.hh"

namespace toppartner
{

namespace branch
{

SignatureSingleBranch::SignatureSingleBranch()
{
    veto_bdt = InitialValue();
}

boca::Observables SignatureSingleBranch::Variables()
{
    return ThreeBody::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}");
}

}

}
