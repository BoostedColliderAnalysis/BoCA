/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/ZHadronic.hh"

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
