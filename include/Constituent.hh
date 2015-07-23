#pragma once

#include "Family.hh"

namespace analysis {

enum class SubDetector {
    none, gen_particle, track, photon, tower, muon
};

class Constituent {

public:

    Constituent();

    Constituent(const TLorentzVector& momentum, const TLorentzVector& position, const Family& family);

    Constituent(const TLorentzVector& momentum, const TLorentzVector& position);

    Constituent(const TLorentzVector& momentum, const TLorentzVector& position, const SubDetector sub_detector, float charge = 0);

    Constituent(const TLorentzVector& momentum, const Family& family);

    Constituent(const LorentzVector& momentum, const Family& family);

    Constituent(const TLorentzVector& momentum);

    Constituent(const TLorentzVector& momentum, const SubDetector sub_detector, float charge);

    Constituent(const TLorentzVector& momentum, const SubDetector sub_detector);

    void SetPosition(const TLorentzVector& position);

    void SetPosition(float x, float y, float z, float t);

    void SetMomentum(const TLorentzVector& momentum);

    void SetFamily(const Family& family);

    LorentzVector Position() const;

    LorentzVector Momentum() const;

    Family family() const;

    Constituent operator+(const Constituent& constituent);

    void SetDetector(const SubDetector sub_detector);

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
