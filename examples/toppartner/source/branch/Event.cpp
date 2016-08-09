/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/Event.hh"
#include "boca/OBSERVABLE.hh"

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
