/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/units/Prefixes.hh"
#include "boca/multivariant/Observables.hh"

namespace standardmodel
{

using namespace boca::units;

namespace branch
{

/**
 *
 * @brief %LeptonVeto base tree branch
 *
 */
class LeptonVeto
{

public:

    LeptonVeto();

    float lepton_pt;
    float lepton_delta_r;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        lepton_pt = multiplet.Lepton().Pt() / GeV;
        lepton_delta_r = multiplet.Lepton().DeltaR() / rad;
    }

    boca::Observables Variables();

    boca::Observables Spectators();

};

}

}
