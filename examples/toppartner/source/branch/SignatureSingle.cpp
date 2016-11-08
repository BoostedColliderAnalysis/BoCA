/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/branch/SignatureSingle.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace toppartner
{

namespace branch
{

SignatureSingle::SignatureSingle()
{
    veto_bdt = InitialValue();
}

boca::Observables SignatureSingle::Variables()
{
    return Signature::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}");
}

}

}
