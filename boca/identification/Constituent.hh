/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/identification/Family.hh"

namespace boca {

enum class DetectorPart {
    none,
    gen_particle,
    track,
    photon,
    tower,
    muon
};

std::string Name(DetectorPart detector_part);

class Constituent : boost::addable<Constituent>{

public:

    Constituent();

    Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position);

    Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position, boca::Family const& family, boca::DetectorPart detector_part, int charge = 0);

    Constituent(TLorentzVector const& momentum);

    Constituent(TLorentzVector const& momentum, boca::Family const& family, boca::DetectorPart detector_part, int charge);

    Constituent(TLorentzVector const& momentum, std::vector<boca::Family> const& families, boca::DetectorPart detector_part);

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

    bool IsInTracker() const;

    std::vector<boca::Family> Families() const;

    Constituent &operator+=(Constituent const& constituent);

private:

    void SetTracker();

    std::vector<boca::Family> families_;

    LorentzVector<Length> position_;

    LorentzVector<boca::Momentum> momentum_;

    int charge_ = 0;

    boca::DetectorPart detector_part_ = boca::DetectorPart::none;

    bool tracker_;
};

}
