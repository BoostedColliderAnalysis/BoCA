/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class WLeptonic : public boca::branch::TwoBody
{

public:

    WLeptonic();

    float lepton_pt;
    float neutrino_pt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        lepton_pt = multiplet.Singlet1().Pt() / GeV;
        neutrino_pt = multiplet.Singlet2().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(WLeptonic, 1)

};

}

}

}
