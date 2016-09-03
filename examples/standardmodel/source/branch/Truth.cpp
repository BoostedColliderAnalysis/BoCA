/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/Truth.hh"

namespace standardmodel
{

using namespace boca;

namespace branch
{

Truth::Truth()
{
    top_pt = InitialValue();
    bottom_pt = InitialValue();
    w_pt = InitialValue();
    quark_1_pt = InitialValue();
    quark_2_pt = InitialValue();
    delta_r_top = InitialValue();
    delta_r_w = InitialValue();
    rho_top = InitialValue();
    rhow_w = InitialValue();
}

Observables Truth::Variables()
{
    return {};
}

Observables Truth::Spectators()
{
    return {};
}

}

}
