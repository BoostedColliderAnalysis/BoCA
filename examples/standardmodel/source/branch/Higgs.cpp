/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/Higgs.hh"

namespace standardmodel
{

namespace branch
{

Higgs::Higgs()
{}

Observables Higgs::Variables()
{
    return TwoBody::Variables() + BottomBase::Variables() + LeptonVeto::Variables();
}

Observables Higgs::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators() + LeptonVeto::Spectators();
}

}

}
