# ifndef HQuartet_hh
# define HQuartet_hh

# include "HDoublet.hh"

class hanalysis::HQuartet : public HTag
{

public:

    HQuartet() {}

    HQuartet(const hanalysis::HDoublet &NewDoublet1, const hanalysis::HDoublet &NewDoublet2);

    ~HQuartet();

    inline HDoublet GetDoublet1()const {
        return Doublet1;
    }

    inline HDoublet GetDoublet2()const {
        return Doublet2;
    }

    inline fastjet::PseudoJet GetDoublet1Jet() const {
        return Doublet1.Jet();
    }

    inline fastjet::PseudoJet GetDoublet2Jet() const {
        return Doublet2.Jet();
    }

    inline fastjet::PseudoJet GetJet() const {
        return GetDoublet1Jet() + GetDoublet2Jet();
    }

    inline float GetHt() {
        return Doublet1.Ht() + Doublet2.Ht();
    }

    inline float GetDeltaPt() const {
        return GetDoublet1Jet().pt() - GetDoublet2Jet().pt();
    }

    inline float GetDeltaRap() const {
        return std::abs(GetDoublet1Jet().rap() - GetDoublet2Jet().rap());
    }

    inline float GetDeltaPhi() const {
        return GetDoublet1Jet().delta_phi_to(GetDoublet2Jet());
    }

    inline float GetDeltaR() const {
        return GetDoublet1Jet().delta_R(GetDoublet2Jet());
    }

    inline float GetMassDifferenceTo(const HParticleId ParticleId) const {
        return std::abs(GetJet().m() - GetParticleMass(ParticleId));
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet";
    };

private:

    HDoublet Doublet1;

    HDoublet Doublet2;

};

#endif
