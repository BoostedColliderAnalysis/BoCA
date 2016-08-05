/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/NewEvent3.hh"
#include "boca/OBSERVABLE.hh"

namespace toppartner
{

namespace branch
{

NewEvent3::NewEvent3()
{
    signature_bdt = InitialValue();
}

boca::Observables NewEvent3::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

boca::Observables NewEvent3::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

}

}
