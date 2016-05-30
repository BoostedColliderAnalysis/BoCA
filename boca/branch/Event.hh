/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Multi.hh"

namespace boca
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class Event : public Multi
{
public:
    Event();

    float lepton_number;
    float jet_number;
    float bottom_number;
    float missing_et;
    float scalar_ht;

    float lepton_ht;
    float jet_mass;
    float jet_pt;
    float jet_ht;
    float jet_rap;
    float jet_phi;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        lepton_number = multiplet.GlobalObservables().LeptonNumber();
        jet_number = multiplet.GlobalObservables().JetNumber();
        bottom_number = multiplet.GlobalObservables().BottomNumber();
        missing_et = multiplet.GlobalObservables().MissingEt() / GeV;
        scalar_ht = multiplet.GlobalObservables().ScalarHt() / GeV;
        lepton_ht = multiplet.GlobalObservables().LeptonHt() / GeV;
        jet_mass = multiplet.Rest().Mass() / GeV;
        jet_pt = multiplet.Rest().Pt() / GeV;
        jet_ht = multiplet.GlobalObservables().JetHt() / GeV;
        jet_rap = multiplet.Rest().Rap() / rad;
        jet_phi = multiplet.Rest().Phi() / rad;
    }

    Observables Variables();

private:

    ClassDef(Event, 1)

};

}

}
