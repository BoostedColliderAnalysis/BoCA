# pragma once

# include "Doublet.hh"

namespace analysis
{

class Quartet22 : public Identification
{

public:

    Quartet22() {}

    Quartet22(const Doublet &doublet_1, const Doublet &doublet_2);

    inline Doublet Getdoublet1()const {
        return doublet_1_;
    }

    inline Doublet Getdoublet2()const {
        return doublet_2_;
    }

    inline fastjet::PseudoJet Getdoublet1Jet() const {
        return doublet_1_.Jet();
    }

    inline fastjet::PseudoJet Getdoublet2Jet() const {
        return doublet_2_.Jet();
    }

    inline fastjet::PseudoJet GetJet() const {
        return Getdoublet1Jet() + Getdoublet2Jet();
    }

    inline float GetHt() {
        return doublet_1_.Ht() + doublet_2_.Ht();
    }

    inline float GetDeltaPt() const {
        return Getdoublet1Jet().pt() - Getdoublet2Jet().pt();
    }

    inline float GetDeltaRap() const {
        return std::abs(Getdoublet1Jet().rap() - Getdoublet2Jet().rap());
    }

    inline float GetDeltaPhi() const {
        return Getdoublet1Jet().delta_phi_to(Getdoublet2Jet());
    }

    inline float GetDeltaR() const {
        return Getdoublet1Jet().delta_R(Getdoublet2Jet());
    }

    inline float GetMassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(GetJet().m() - GetParticleMass(particle_id));
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quartet22";
    }

private:

    Doublet doublet_1_;

    Doublet doublet_2_;

};

}
