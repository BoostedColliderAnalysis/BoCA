/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Event.hh"
#include "boca/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

Event::Event()
{
    lepton_number = static_cast<int>(InitialValue());
    jet_number = static_cast<int>(InitialValue());
    bottom_number = static_cast<int>(InitialValue());
    missing_et = InitialValue();
    scalar_ht = InitialValue();
    lepton_ht = InitialValue();
    jet_mass = InitialValue();
    jet_pt = InitialValue();
    jet_ht = InitialValue();
    jet_rap = InitialValue();
    jet_phi = InitialValue();
}

Observables Event::Variables()
{
    return Multi::Variables() + OBSERVABLE(lepton_number, "#l") + OBSERVABLE(bottom_number, "#b") + OBSERVABLE(jet_number, "#j") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}^{scalar}") + OBSERVABLE(lepton_ht, "H_{T}^{l}") + OBSERVABLE(jet_mass, "m_{j}") + OBSERVABLE(jet_pt, "p_{T}^{j}") + OBSERVABLE(jet_ht, "H_{T}^{j}") + OBSERVABLE(jet_rap, "\\eta_{j}") + OBSERVABLE(jet_phi, "\\phi_{j}");
}

}

}
