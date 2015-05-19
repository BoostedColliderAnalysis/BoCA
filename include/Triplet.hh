# pragma once

# include "Doublet.hh"

namespace analysis{

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

class Triplet : public Identification
{

public:

    Triplet();

    Triplet(const Doublet &doublet, const fastjet::PseudoJet &singlet);

    Triplet(const fastjet::PseudoJet &singlet);

    Doublet doublet() const;

    fastjet::PseudoJet singlet()const;

    inline fastjet::PseudoJet doublet_jet() const {
        return doublet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (doublet_jet() + singlet());
    }

    inline float GetJetDeltaMass(const ParticleId particle_id) const {
        return std::abs(singlet().m() - GetParticleMass(particle_id));
    }

    inline float GetDeltaMass(const ParticleId particle_id) const {
        return std::abs(Jet().m() - GetParticleMass(particle_id));
    }

    inline float Ht() const {
        return (doublet().Ht() + singlet().pt());
    }

    inline float DeltaPt() const {
        return (doublet_jet().pt() - singlet().pt());
    }

    inline float DeltaM() const {
        return (doublet_jet().m() - singlet().m());
    }

    inline float DeltaHt() const {
        return (doublet().Ht() - singlet().pt());
    }

    inline float DeltaPhi() const {
        return doublet_jet().delta_phi_to(singlet());
    }

    inline float DeltaRap() const {
        float NewDeltaRap = doublet_jet().rap() - singlet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    inline float DeltaR() const {
        float NewDeltaR = doublet_jet().delta_R(singlet());
        if (std::abs(NewDeltaR) > 100) NewDeltaR = 0;
        return NewDeltaR;
    }

    void set_sub_jettiness(const SubJettiness &n_sub_jettiness) {
        sub_jettiness_ = n_sub_jettiness;
    }

    SubJettiness sub_jettiness() const {
        return sub_jettiness_;
    }

    float SingletBdt() const {
      return singlet().user_info<JetInfo>().Bdt();
    }

//     float DoubletBdt() const {
//       return Doublet().Bdt();
//     }

    float LeptonPt = 0; // FIXME we want to get rid of this again

protected:

//     Triplet(TripletPrivate& NewtripletPrivate) ;

    virtual inline std::string ClassName() const {
        return "Triplet";
    }


private:

    void SetSinglet(const fastjet::PseudoJet &NewSinglet);

    void Setdoublet(const Doublet &doublet);

    Doublet doublet_;

    fastjet::PseudoJet singlet_;

    SubJettiness sub_jettiness_;

};

}
