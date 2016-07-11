/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Bdt.hh"
#include "boca/OBSERVABLE.hh"
// #define INFORMATION
// #include "boca/generic/DEBUG.hh"

namespace boca
{

namespace branch
{

Bdt::Bdt()
{
    bdt = InitialValue();
}

Observables Bdt::Variables()
{
    return Result::Variables();
}

Observables Bdt::Spectators()
{
    return Result::Spectators() + OBSERVABLE(bdt);
}

}

}
