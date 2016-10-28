/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "tthh/branch/Signature.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace tthh
{

namespace branch
{

Signature::Signature()
{
    veto_bdt = InitialValue();
}

boca::Observables Signature::Variables()
{
    return boca::branch::Signature::Variables() + OBSERVABLE(veto_bdt, "BDT_{V}");
}

}

}
