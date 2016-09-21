/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "tthh/branch/Higgs.hh"

namespace tthh
{

namespace branch
{

Higgs::Higgs()
{}

boca::Observables Higgs::Variables()
{
    return TwoBody::Variables() + BottomBase::Variables();
}

boca::Observables Higgs::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}
