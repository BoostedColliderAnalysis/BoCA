/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Prefixes.hh"
#include "boca/branch/Result.hh"

namespace standardmodel
{

using namespace boca;

namespace branch {

/**
 *
 * @brief %Truth tagger tree branch
 *
 */
class Truth : public boca::branch::Result
{
public:
    Truth();
    float top_pt;
    float bottom_pt;
    float w_pt;
    float quark_1_pt;
    float quark_2_pt;
    float delta_r_top;
    float delta_r_w;
    float rho_top;
    float rhow_w;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        top_pt = multiplet.TopPt() / GeV;
        bottom_pt = multiplet.BottomPt() / GeV;
        w_pt = multiplet.WPt() / GeV;
        quark_1_pt = multiplet.Quark1Pt() / GeV;
        quark_2_pt = multiplet.Quark2Pt() / GeV;
        delta_r_top = multiplet.DeltaRTop() / rad;
        delta_r_w = multiplet.DeltaRW() / rad;
        rho_top = multiplet.RhoTop();
        rhow_w = multiplet.RhoW();
    }

    boca::Observables Variables();

    boca::Observables Spectators();

private:

    ClassDef(Truth, 1)

};


}

}
