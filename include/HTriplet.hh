# ifndef HTriplet_hh
# define HTriplet_hh

# include "HDoublet.hh"

class HTripletPrivate;

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

class hanalysis::HTriplet : public HTag
{

public:

    HTriplet();

    HTriplet(const hanalysis::HDoublet &NewDoublet, const fastjet::PseudoJet &NewSinglet);

    HTriplet(const fastjet::PseudoJet &NewSinglet);

    ~HTriplet();

    HDoublet Doublet()const;

    fastjet::PseudoJet Singlet()const;

    inline fastjet::PseudoJet DoubletJet() const {
        return Doublet().Jet();
    }
    inline fastjet::PseudoJet Jet() const {
        return (DoubletJet() + Singlet());
    }

    inline float GetJetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(Singlet().m() - GetParticleMass(ParticleId));
    }

    inline float GetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float Ht() const {
        return (Doublet().Ht() + Singlet().pt());
    }

    inline float DeltaPt() const {
        return (DoubletJet().pt() - Singlet().pt());
    }

    inline float DeltaM() const {
        return (DoubletJet().m() - Singlet().m());
    }

    inline float DeltaHt() const {
        return (Doublet().Ht() - Singlet().pt());
    }

    inline float DeltaPhi() const {
        return DoubletJet().delta_phi_to(Singlet());
    }

    inline float DeltaRap() const {
        float NewDeltaRap = DoubletJet().rap() - Singlet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    inline float DeltaR() const {
        float NewDeltaR = DoubletJet().delta_R(Singlet());
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

//     HTriplet(HTripletPrivate& NewTripletPrivate) ;

    virtual inline std::string ClassName() const {
        return "HTriplet";
    }


private:

    void SetSinglet(const fastjet::PseudoJet &NewSinglet);

    void SetDoublet(const HDoublet &NewDoublet);

    HDoublet doublet_;

    fastjet::PseudoJet singlet_;

    SubJettiness sub_jettiness_;


//   HTripletPrivate * Triplet;

//     HDoublet Doublet;

//     fastjet::PseudoJet Singlet;

};

#endif
