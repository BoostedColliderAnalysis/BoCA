/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/NewEvent2.hh"
#include "boca/OBSERVABLE.hh"

namespace toppartner
{

namespace branch
{

NewEvent2::NewEvent2()
{
    veto_bdt = InitialValue();
    signature_bdt = InitialValue();
}

boca::Observables NewEvent2::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(veto_bdt, "BDT_{veto}") + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

boca::Observables NewEvent2::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

}

}
