/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Rtypes.h"

#include "boca/physics/Prefixes.hh"

#include "boca/Observables.hh"

namespace boca
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class GlobalBase
{

public:

    GlobalBase();

    float lepton_number;
    float jet_number;
    float bottom_number;
    float missing_et;
    float scalar_ht;
    float lepton_ht;
    float jet_1_pt;
    float jet_2_pt;
    float jet_3_pt;
    float jet_4_pt;
    float lepton_1_pt;
    float lepton_2_pt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        lepton_number = multiplet.LeptonNumber();
        jet_number = multiplet.JetNumber();
        bottom_number = multiplet.BottomNumber();
        missing_et = multiplet.MissingEt() / GeV;
        scalar_ht = multiplet.ScalarHt() / GeV;
        lepton_ht = multiplet.LeptonHt() / GeV;
        lepton_1_pt = multiplet.LeptonPt(0) / GeV;
        lepton_2_pt = multiplet.LeptonPt(1) / GeV;
        jet_1_pt = multiplet.JetPt(0) / GeV;
        jet_2_pt = multiplet.JetPt(1) / GeV;
        jet_3_pt = multiplet.JetPt(2) / GeV;
        jet_4_pt = multiplet.JetPt(3) / GeV;
    }

    virtual Observables Variables();

    virtual Observables Spectators();

private:
    float InValue();
    ClassDef(GlobalBase, 1)
};

}

}
