# ifndef HQuartet_hh
# define HQuartet_hh

# include "Doublet.hh"

class hanalysis::HQuartet : public HTag
{

public:

    HQuartet() {}

    HQuartet(const hanalysis::Doublet &Newdoublet1, const hanalysis::Doublet &Newdoublet2);

    ~HQuartet();

    inline Doublet Getdoublet1()const {
        return doublet1;
    }

    inline Doublet Getdoublet2()const {
        return doublet2;
    }

    inline fastjet::PseudoJet Getdoublet1Jet() const {
        return doublet1.Jet();
    }

    inline fastjet::PseudoJet Getdoublet2Jet() const {
        return doublet2.Jet();
    }

    inline fastjet::PseudoJet GetJet() const {
        return Getdoublet1Jet() + Getdoublet2Jet();
    }

    inline float GetHt() {
        return doublet1.Ht() + doublet2.Ht();
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

    inline float GetMassDifferenceTo(const HParticleId ParticleId) const {
        return std::abs(GetJet().m() - GetParticleMass(ParticleId));
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet";
    };

private:

    Doublet doublet1;

    Doublet doublet2;

};

#endif
