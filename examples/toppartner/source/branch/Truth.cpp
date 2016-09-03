/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/branch/Truth.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace toppartner
{

namespace branch
{

Truth::Truth()
{
    top_pt = InitialValue();
    lepton_pt = InitialValue();
    softest_boson_pt = InitialValue();
    hardest_boson_pt = InitialValue();
    boson_number = static_cast<int>(InitialValue());
    hard_boson_number = static_cast<int>(InitialValue());
    detectable_boson_number = static_cast<int>(InitialValue());
    boson_delta_r_min = InitialValue();
    missing_et = InitialValue();
    scalar_ht = InitialValue();
    jet_pt = InitialValue();
}

Observables Truth::Variables()
{
    return OBSERVABLE(top_pt, "p_{T}(t)") + OBSERVABLE(lepton_pt, "p_{T}(l)") + OBSERVABLE(hard_boson_number, "#B^{0}_{hard}") + OBSERVABLE(softest_boson_pt, "p_{T}(B^{0})_{soft}") + OBSERVABLE(detectable_boson_number, "#B^{0}_{detect}") + OBSERVABLE(hardest_boson_pt, "p_{T}(B)_{hard}") + OBSERVABLE(boson_delta_r_min, "\\Delta R(B,B)_{min}") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}") + OBSERVABLE(jet_pt, "p_{T}(j)");
}

}

}
