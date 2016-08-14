/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/Bottom.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

Observables Bottom::Variables()
{
    return Particle::Variables() + BottomBase::Variables();
}

Observables Bottom::Spectators()
{
    return Particle::Spectators() + BottomBase::Variables();
}

}

}

}

