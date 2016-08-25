/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Prefixes.hh"
#include "boca/Observables.hh"

namespace boca
{

namespace standardmodel
{

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

    Observables Variables();

    Observables Spectators();

};

}

}

}
