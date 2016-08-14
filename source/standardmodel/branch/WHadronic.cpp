/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/WHadronic.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace boca
{

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

}
