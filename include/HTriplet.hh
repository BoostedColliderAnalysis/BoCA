# ifndef HTriplet_hh
# define HTriplet_hh

# include "HDoublet.hh"

class hanalysis::HTriplet : public HTag
{

public:

    HTriplet();

    HTriplet(const hanalysis::HDoublet &NewDoublet, const fastjet::PseudoJet &NewJet);

    ~HTriplet();

    fastjet::PseudoJet GetDoubletJet() const {
        return Doublet.GetDoubletJet();
    }

    fastjet::PseudoJet GetTripletJet() const {
        return (GetDoubletJet() + Jet);
    }

    inline float GetJetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(Jet.m() - GetParticleMass(ParticleId));
    }

    inline float GetDeltaMass(const HParticleId ParticleId) const {
        return std::abs(GetTripletJet().m() - GetParticleMass(ParticleId));
    }

    inline float GetHt() const {
        return (Jet.pt() + Doublet.GetHt());
    }

    inline float GetDeltaPt() const {
        return std::abs(Jet.pt() - GetDoubletJet().pt());
    }

    inline float GetDeltaPhi() const {
        return (Jet.delta_phi_to(GetDoubletJet()));
    }

    inline float GetDeltaRap() const {
        return (std::abs(Jet.rap() - GetDoubletJet().rap()));
    }

    inline float GetDeltaR() const {
        return (Jet.delta_R(GetDoubletJet()));
    }

    inline HDoublet GetDoublet()const {
        return Doublet;
    }

    inline fastjet::PseudoJet GetSinglet()const {
        return Jet;
    }

protected:

    HDoublet Doublet;

    fastjet::PseudoJet Jet;

    virtual inline std::string ClassName() const {
        return "HTriplet";
    };

private:

};

#endif
