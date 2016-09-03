/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/WHadronic.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace standardmodel
{

namespace branch
{

Observables WHadronic::Variables()
{
    return TwoBody::Variables() + BottomBase::Variables();
}

Observables WHadronic::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}
