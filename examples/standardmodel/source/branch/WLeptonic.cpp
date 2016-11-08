/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/WLeptonic.hh"
#include "boca/branch/Base.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

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
    return Result::Variables() + OBSERVABLE(pt, latex::String("p_T") + " [GeV]") + OBSERVABLE(ht,  "H_{T}") + OBSERVABLE(delta_pt, "\\Delta p_{T}") + OBSERVABLE(delta_rap, "\\Delta y") + OBSERVABLE(delta_phi, "\\Delta \\phi") + OBSERVABLE(delta_r, "\\Delta R") + OBSERVABLE(rho, "\\rho") + OBSERVABLE(lepton_pt, "p_{T}(l)") + OBSERVABLE(neutrino_pt, "p_{T}(\\nu)");
}

}

}
