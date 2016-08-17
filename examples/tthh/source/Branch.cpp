/**
 * Copyright (C) 2015-2016 Jan Hajer
 */;
#include "boca/OBSERVABLE_MACROS.hh"

#include "include/Branch.hh"


Branch::Branch()
{
    jet_number = static_cast<int>(InitialValue());
    bottom_number = static_cast<int>(InitialValue());
    missing_et = InitialValue();
    scalar_ht = InitialValue();
    jet_1_pt = InitialValue();
    jet_2_pt = InitialValue();
    jet_3_pt = InitialValue();
    jet_4_pt = InitialValue();
}

boca::Observables Branch::Variables()
{
    return boca::branch::Bdt::Variables() + OBSERVABLE(bottom_number, "#b") + OBSERVABLE(jet_number, "#j") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}^{scalar}") + OBSERVABLE(jet_1_pt, "p_{T}(j_{1})") + OBSERVABLE(jet_2_pt, "p_{T}(j_{2})") + OBSERVABLE(jet_3_pt, "p_{T}(j_{3})") + OBSERVABLE(jet_4_pt, "p_{T}(j_{4})");
}

boca::Observables Branch::Spectators()
{
    return boca::branch::Bdt::Spectators();
}
