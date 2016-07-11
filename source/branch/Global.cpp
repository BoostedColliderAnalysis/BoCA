/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Global.hh"

namespace boca
{

namespace branch
{

Global::Global()
{}

Observables Global::Variables()
{
    return Bdt::Variables() + GlobalBase::Variables();
}

Observables Global::Spectators()
{
    return Bdt::Spectators() + GlobalBase::Spectators();
}

}

}
