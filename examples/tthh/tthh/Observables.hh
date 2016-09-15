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

    Observables();

    Observables(boca::Event const &event);

    Observables(boca::Event const &event, std::vector<boca::Jet> const &jets);

    void SetEvent(boca::Event const &event, std::vector<boca::Jet> const &jets);

    void SetEvent(boca::Event const &event);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    boca::Momentum ScalarHt() const;

    boca::Momentum LeptonHt() const;

    boca::Momentum JetHt() const;

    boca::Momentum Ht() const;

    boca::Mass Mass() const;

    boca::Angle DeltaRTo(boca::PseudoJet const &jet) const;

    int Charge() const;

    boca::Momentum JetPt(std::size_t number) const;

    boca::Momentum PhotonPt(std::size_t number) const;

    boca::Momentum LeptonPt(std::size_t number) const;

    boca::Energy MissingEt() const;

    std::vector<boca::Jet> Jets() const;

    void SetJets(std::vector<boca::Jet> const &jets);

    void SetLeptons(std::vector<boca::Lepton> const &leptons);

    void SetPhotons(std::vector<boca::Photon> const &photons);

    boca::Singlet ConstituentJet() const;

    boca::Jet Jet() const;

    std::vector<boca::Jet> Constituents() const;

    std::vector<boca::LorentzVector<boca::Momentum>> LorentzVectors() const;

private:

    std::vector<boca::Jet> jets_;

    std::vector<boca::Lepton> leptons_;

    std::vector<boca::Photon> photons_;

    boca::Momentum scalar_ht_;

    boca::Energy missing_et_;

    boca::Mutable<boca::Jet> jet_;

    boca::Mutable<boca::Singlet> constituent_jet_;

};

}
