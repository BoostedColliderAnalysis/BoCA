/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Multi.hh"
#include "boca/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

Multi::Multi()
{
    delta_ht = InitialValue();
}

Observables Multi::Variables()
{
    return TwoBody::Variables() + OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]");
}

}

}
