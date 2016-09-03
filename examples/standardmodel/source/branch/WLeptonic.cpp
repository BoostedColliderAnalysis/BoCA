/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/WLeptonic.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace standardmodel
{

using namespace boca;

namespace branch
{

WLeptonic::WLeptonic()
{
    neutrino_pt = InitialValue();
    lepton_pt = InitialValue();
}

Observables WLeptonic::Variables()
{
    return Result::Variables() + OBSERVABLE(pt, latex::String("p_T") + " [GeV]") + OBSERVABLE(ht) + OBSERVABLE(delta_pt) + OBSERVABLE(delta_rap) + OBSERVABLE(delta_phi) + OBSERVABLE(delta_r) + OBSERVABLE(rho) + OBSERVABLE(lepton_pt) + OBSERVABLE(neutrino_pt);
}

}

}
