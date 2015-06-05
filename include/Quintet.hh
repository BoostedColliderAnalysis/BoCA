# pragma once

# include "Triplet.hh"

namespace analysis
{

class Quintet : public Identification
{

public:

    Quintet() {}

    Quintet(const Triplet &triplet, const Doublet &doublet);

    inline Doublet doublet()const {
        return doublet_;
    }

    inline Triplet triplet()const {
        return triplet_;
    }

    inline fastjet::PseudoJet doublet_jet() const {
        return doublet_.Jet();
    }

    inline fastjet::PseudoJet triplet_jet() const {
        return triplet_.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return doublet_jet() + triplet_jet();
    }

    inline float Ht() const {
        return doublet_.Ht() + triplet_.Ht();
    }

    inline float DeltaHt() const {
      return triplet_.Ht() - doublet_.Ht();
    }

    inline float DeltaPt() const {
        return doublet_jet().pt() - triplet_jet().pt();
    }

    inline float DeltaRap() const {
        return std::abs(doublet_jet().rap() - triplet_jet().rap());
    }

    inline float DeltaPhi() const {
        return doublet_jet().delta_phi_to(triplet_jet());
    }

    inline float DeltaR() const {
        return doublet_jet().delta_R(triplet_jet());
    }

    inline float DeltaM() const {
      return doublet_jet().m() - triplet_jet().m();
    }

    inline float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - Mass(particle_id));
    }

    bool overlap() const;

    Triplet SubMultiplet1() const {
      return triplet_;
    }

    Doublet SubMultiplet2() const {
      return doublet_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quintet";
    }

private:

    Doublet doublet_;

    Triplet triplet_;

    DetectorGeometry detector_geometry_;
};

}
