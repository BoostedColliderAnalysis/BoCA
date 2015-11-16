/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "LorentzVector.hh"

namespace boca {

enum class SubDetector {
    none, gen_particle, track, photon, tower, muon
};

class Constituent {

public:

    Constituent();

    Constituent(TLorentzVector const& momentum, LorentzVector const& position);

    Constituent(TLorentzVector const& momentum, LorentzVector const& position, SubDetector sub_detector, float charge = 0);

    Constituent(TLorentzVector const& momentum);

    Constituent(TLorentzVector const& momentum, SubDetector sub_detector, float charge);

    Constituent(TLorentzVector const& momentum, SubDetector sub_detector);

    void SetPosition(TLorentzVector const& position);

    void SetPosition(float x, float y, float z, float t);

    void SetMomentum(TLorentzVector const& momentum);

    LorentzVector Position() const;

    LorentzVector Momentum() const;

    Constituent operator+(Constituent const& constituent);

    void SetDetector(SubDetector sub_detector);

    SubDetector sub_detector() const;

    int charge() const;

    void set_charge(int charge);

private:

    SubDetector sub_detector_ = SubDetector::none;

    LorentzVector position_;

    LorentzVector momentum_;

    int charge_ = 0;
};

}
