/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/ZHadronic.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

Observables ZHadronic::Variables()
{
    return TwoBody::Variables() + BottomBase::Variables();
}

Observables ZHadronic::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}

}
