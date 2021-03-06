/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/branch/Event.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace toppartner
{

namespace branch
{

Event::Event()
{
    veto_bdt = InitialValue();
}

boca::Observables Event::Variables()
{
    return boca::branch::Event::Variables() + OBSERVABLE(veto_bdt, "BDT_{veto}");
}

}

}
