/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/NewEvent.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace toppartner
{

namespace branch
{

NewEvent::NewEvent()
{
    global_bdt = InitialValue();
    signature_bdt = InitialValue();
}

Observables NewEvent::Variables()
{
    return Bdt::Variables() + OBSERVABLE(global_bdt, "BDT_{global}") + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

}

}
