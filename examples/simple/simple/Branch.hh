/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Prefixes.hh"
#include "boca/branch/Bdt.hh"
#include "boca/Observables.hh"

namespace simple
{

class Branch :  public boca::branch::Bdt
{

public:

    Branch();

    float jet_number;
    float bottom_number;
    float missing_et;
    float scalar_ht;
    float jet_1_pt;
    float jet_2_pt;
    float jet_3_pt;
    float jet_4_pt;

    template<typename Multiplet>
    void Fill(Multiplet const &multiplet)
    {
        boca::branch::Bdt::Fill(multiplet);
        jet_number = multiplet.JetNumber();
        bottom_number = multiplet.BottomNumber();
        missing_et = multiplet.MissingEt() / boca::GeV;
        scalar_ht = multiplet.ScalarHt() / boca::GeV;
        jet_1_pt = multiplet.JetPt(0) / boca::GeV;
        jet_2_pt = multiplet.JetPt(1) / boca::GeV;
        jet_3_pt = multiplet.JetPt(2) / boca::GeV;
        jet_4_pt = multiplet.JetPt(3) / boca::GeV;
    }

    boca::Observables Variables() override;

    boca::Observables Spectators() override;

private:
    ClassDef(Branch, 1)
};

}
