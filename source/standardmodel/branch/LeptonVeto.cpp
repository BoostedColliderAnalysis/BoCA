/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/LeptonVeto.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

LeptonVeto::LeptonVeto()
{
    lepton_pt = boca::branch::Base::InitialValue();
    lepton_delta_r = boca::branch::Base::InitialValue();
}

Observables LeptonVeto::Variables()
{
    return OBSERVABLE(lepton_pt) + OBSERVABLE(lepton_delta_r);
}

Observables LeptonVeto::Spectators()
{
    return {};
}

}

}

}
