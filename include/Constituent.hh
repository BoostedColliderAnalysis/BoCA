/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "math/LorentzVector.hh"

namespace boca {

enum class DetectorPart {
    none,
    gen_particle,
    track,
    photon,
    tower,
    muon
};

class Constituent {

public:

    Constituent();

    Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position);

    Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position, boca::DetectorPart detector_part, int charge = 0);

    Constituent(TLorentzVector const& momentum);

    Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part, int charge);

    Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part);

    void SetMomentum(TLorentzVector const& momentum);

    void SetCharge(int charge);

    void SetDetectorPart(boca::DetectorPart detector_part);

    LorentzVector<Length> const& Position() const;

    LorentzVector<boca::Momentum> const& Momentum() const;

    LorentzVector<Length> & Position();

    LorentzVector<boca::Momentum> & Momentum();

    boca::DetectorPart DetectorPart() const;

    int Charge() const;

    void Smearing();

    Constituent operator+(Constituent const& constituent);

private:

    boca::DetectorPart detector_part_ = boca::DetectorPart::none;

    LorentzVector<Length> position_;

    LorentzVector<boca::Momentum> momentum_;

    int charge_ = 0;
};

}
