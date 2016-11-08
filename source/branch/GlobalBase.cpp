/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Global.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

float GlobalBase::InValue()
{
    return Base::InitialValue();
}

GlobalBase::GlobalBase()
{
    lepton_number = static_cast<int>(InValue());
    jet_number = static_cast<int>(InValue());
    bottom_number = static_cast<int>(InValue());
    missing_et = InValue();
    scalar_ht = InValue();
    lepton_ht = InValue();
    jet_1_pt = InValue();
    jet_2_pt = InValue();
    jet_3_pt = InValue();
    jet_4_pt = InValue();
    lepton_1_pt = InValue();
    lepton_2_pt = InValue();
}

Observables GlobalBase::Variables()
{
    return OBSERVABLE(lepton_number, "#l") + OBSERVABLE(bottom_number, "#b") + OBSERVABLE(jet_number, "#j") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}^{scalar}") + OBSERVABLE(lepton_ht, "H_{T}^{l}") + OBSERVABLE(jet_1_pt, "p_{T}(j_{1})") + OBSERVABLE(jet_2_pt, "p_{T}(j_{2})") + OBSERVABLE(jet_3_pt, "p_{T}(j_{3})") + OBSERVABLE(jet_4_pt, "p_{T}(j_{4})") + OBSERVABLE(lepton_1_pt, "p_{T}(l_{1})") + OBSERVABLE(lepton_2_pt, "p_{T}(l_{2})");
}

Observables GlobalBase::Spectators()
{
    return {};
}

}

}
