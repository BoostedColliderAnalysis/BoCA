/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Singlet.hh"

namespace boca
{
class Event;
}

namespace tthh {

class Observables : public boca::Identification
{

public:

    Observables(boca::Event const &event);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    boca::Momentum ScalarHt() const;

    boca::Momentum LeptonHt() const;

    boca::Momentum JetHt() const;

    boca::Momentum Ht() const;

    boca::Mass Mass() const;

    boca::Momentum JetPt(unsigned number) const;

    boca::Momentum PhotonPt(unsigned number) const;

    boca::Momentum LeptonPt(unsigned number) const;

    boca::Mass PhotonPM() const;

    boca::Energy MissingEt() const;

    std::vector<boca::Jet> Jets() const;

private:

    std::vector<boca::Jet> jets_;

    std::vector<boca::Lepton> leptons_;

    std::vector<boca::Photon> photons_;

    boca::Momentum scalar_ht_;

    boca::Energy missing_et_;

};

}
