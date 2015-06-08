# pragma once

# include "Family.hh"

namespace analysis
{

class Constituent
{

public:

    enum SubDetector {kGenParticle, kTrack, kPhoton, kTower, kMuon, kNone};

    Constituent();

    Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const Family &family);

    Constituent(const TLorentzVector &momentum, const TLorentzVector &position);

    Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const SubDetector sub_detector);

    Constituent(const TLorentzVector &momentum, const Family &family);

    Constituent(const TLorentzVector &momentum);

    Constituent(const TLorentzVector &momentum, const SubDetector sub_detector);

    void SetPosition(const TLorentzVector &position);

    void SetPosition(const float x, const float y, const float z, const float t);

    void SetMomentum(const TLorentzVector &momentum);

    void SetFamily(const Family& family);

    TLorentzVector Position() const;

    TLorentzVector Momentum() const;

    Family family() const;

    Constituent operator+(Constituent& constituent);

    void SetDetector(const SubDetector sub_detector);

    SubDetector sub_detector() const;

private:

    SubDetector sub_detector_ = kNone;

    TLorentzVector position_;

    TLorentzVector momentum_;

    analysis::Family family_;
};

}
