/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Family.hh"

namespace analysis {

enum class SubDetector {
    none, gen_particle, track, photon, tower, muon
};

class Constituent {

public:

    Constituent();

    Constituent(TLorentzVector const& momentum, LorentzVector const& position, Family const& family);

    Constituent(TLorentzVector const& momentum, LorentzVector const& position);

    Constituent(TLorentzVector const& momentum, LorentzVector const& position, SubDetector sub_detector, float charge = 0);

    Constituent(TLorentzVector const& momentum, Family const& family);

    Constituent(LorentzVector const& momentum, Family const& family);

    Constituent(TLorentzVector const& momentum);

    Constituent(TLorentzVector const& momentum, SubDetector sub_detector, float charge);

    Constituent(TLorentzVector const& momentum, SubDetector sub_detector);

    void SetPosition(TLorentzVector const& position);

    void SetPosition(float x, float y, float z, float t);

    void SetMomentum(TLorentzVector const& momentum);

    void SetFamily(Family const& family);

    LorentzVector Position() const;

    LorentzVector Momentum() const;

    Family family() const;

    Constituent operator+(Constituent const& constituent);

    void SetDetector(SubDetector sub_detector);

    SubDetector sub_detector() const;

    int charge() const;

    void set_charge(int charge);

private:

    SubDetector sub_detector_ = SubDetector::none;

    LorentzVector position_;

    LorentzVector momentum_;

    analysis::Family family_;

    int charge_ = 0;
};

}
