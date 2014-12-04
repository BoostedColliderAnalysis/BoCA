# ifndef HPair_hh
# define HPair_hh

# include "HTag.hh"

class hanalysis::HPair : public HTag
{

public:

  HPair();
  
  HPair(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

    ~HPair();

    fastjet::PseudoJet GetPairJet() const {
        return (Jet1 + Jet2);
    }

    inline float GetInvariantMass() const {
        return (GetPairJet().m());
    }

    inline float GetMassDifference(const int ParticleMass) const {
        return std::abs(GetInvariantMass() - ParticleMass);
    }

    inline float GetMassDifference(const HParticleId ParticleId) const {
        return std::abs(GetInvariantMass() - GetParticleMass(ParticleId));
    }

    inline float GetPtSum() const {
        return (Jet1.pt() + Jet2.pt());
    }

    inline float GetPtDiff() const {
        return std::abs(Jet1.pt() - Jet2.pt());
    }

    inline float GetPhiDelta() const {
        return (Jet1.delta_phi_to(Jet2));
    }

    inline float GetDeltaRap() const {
        return (std::abs(Jet1.rap() - Jet2.rap()));
    }

    inline float GetDeltaR() const {
        return (Jet1.delta_R(Jet2));
    }

    fastjet::PseudoJet GetJet1()const{return Jet1;}

    fastjet::PseudoJet GetJet2()const{return Jet2;}

protected:

    fastjet::PseudoJet Jet1;

    fastjet::PseudoJet Jet2;

    virtual inline std::string ClassName() const {
        return "HPair";
    };

private:

};

#endif
