/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Event.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace branch
{

Event::Event()
{
    signature_bdt = InitialValue();
}

boca::Observables Event::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables() + OBSERVABLE(signature_bdt, "BDT_{Signature}");
}

boca::Observables Event::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

}

}
