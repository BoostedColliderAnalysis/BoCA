# pragma once

# include "Doublet.hh"

class TripletPrivate;

struct SubJettiness {
    float tau1_beta1;
    float tau2_beta1;
    float tau3_beta1;
    float tau21_beta1;
    float tau32_beta1;

    float tau1_beta2;
    float tau2_beta2;
    float tau3_beta2;
    float tau21_beta2;
    float tau32_beta2;
};

class hanalysis::Triplet : public HTag
{

public:

    Triplet();

    Triplet(const hanalysis::Doublet &Newdoublet, const fastjet::PseudoJet &NewSinglet);

    Triplet(const fastjet::PseudoJet &NewSinglet);

    Doublet doublet()const;

    fastjet::PseudoJet Singlet()const;

    inline fastjet::PseudoJet doublet_jet() const {
        return doublet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (doublet_jet() + Singlet());
    }

    inline float GetJetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(Singlet().m() - GetParticleMass(ParticleId));
    }

    inline float GetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float Ht() const {
        return (doublet().Ht() + Singlet().pt());
    }

    inline float DeltaPt() const {
        return (doublet_jet().pt() - Singlet().pt());
    }

    inline float DeltaM() const {
        return (doublet_jet().m() - Singlet().m());
    }

    inline float DeltaHt() const {
        return (doublet().Ht() - Singlet().pt());
    }

    inline float DeltaPhi() const {
        return doublet_jet().delta_phi_to(Singlet());
    }

    inline float DeltaRap() const {
        float NewDeltaRap = doublet_jet().rap() - Singlet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    inline float DeltaR() const {
        float NewDeltaR = doublet_jet().delta_R(Singlet());
        if (std::abs(NewDeltaR) > 100) NewDeltaR = 0;
        return NewDeltaR;
    }

    void set_sub_jettiness(const SubJettiness &n_sub_jettiness) {
        sub_jettiness_ = n_sub_jettiness;
    }

    SubJettiness sub_jettiness() const {
        return sub_jettiness_;
    }

    float LeptonPt = 0; // FIXME we want to get rid of this again

protected:

//     Triplet(TripletPrivate& NewtripletPrivate) ;

    virtual inline std::string ClassName() const {
        return "Triplet";
    }


private:

    void SetSinglet(const fastjet::PseudoJet &NewSinglet);

    void Setdoublet(const Doublet &Newdoublet);

    Doublet doublet_;

    fastjet::PseudoJet singlet_;

    SubJettiness sub_jettiness_;


//   TripletPrivate * triplet;

//     Doublet doublet;

//     fastjet::PseudoJet Singlet;

};
