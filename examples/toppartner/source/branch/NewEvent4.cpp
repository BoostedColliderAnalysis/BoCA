/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/NewEvent4.hh"
#include "boca/OBSERVABLE.hh"

namespace toppartner
{

namespace branch
{

NewEvent4::NewEvent4()
{
    signature_bdt = InitialValue();
}

boca::Observables NewEvent4::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + EventShapesBase::Variables() + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

boca::Observables NewEvent4::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators() + EventShapesBase::Spectators();
}

}

}
