# ifndef HTriple_hh
# define HTriple_hh

# include "HJetLeptonPair.hh"

class hanalysis::HTriple : public HTag
{

public:

    HTriple();

    HTriple(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2, const fastjet::PseudoJet &NewJet3);

    HTriple(const fastjet::PseudoJet &NewJet, const HJetLeptonPair &Pair);

    ~HTriple();

    fastjet::PseudoJet GetPairJet() const {
        return (Jet1 + Jet2);
    }

    fastjet::PseudoJet GetTripleJet() const {
        return (Jet1 + Jet2 + Jet3);
    }

    inline float GetPairInvariantMass() const {
        return (GetPairJet().m());
    }

    inline float GetTripleInvariantMass() const {
        return (GetTripleJet().m());
    }

//     inline float GetPairMassDifference(const int ParticleMass) const {
//         return std::abs(GetPairInvariantMass() - ParticleMass);
//     }

    inline float GetJet1MassDifference(const HParticleId ParticleId) const {
        return std::abs(Jet1.m() - GetParticleMass(ParticleId));
    }

    inline float GetPairMassDifference(const HParticleId ParticleId) const {
        return std::abs(GetPairInvariantMass() - GetParticleMass(ParticleId));
    }

//     inline float GetTripleMassDifference(const int ParticleMass) const {
//       return std::abs(GetTripleInvariantMass() - ParticleMass);
//     }

    inline float GetTripleMassDifference(const HParticleId ParticleId) const {
        return std::abs(GetTripleInvariantMass() - GetParticleMass(ParticleId));
    }

    inline float GetPairPtSum() const {
        return (Jet1.pt() + Jet2.pt());
    }

    inline float GetPairPtDiff() const {
        return std::abs(Jet1.pt() - Jet2.pt());
    }

    inline float GetTriplePtSum() const {
        return (Jet3.pt() + GetPairJet().pt());
    }

    inline float GetTriplePtDiff() const {
        return std::abs(Jet3.pt() - GetPairJet().pt());
    }

    inline float GetPairDeltaPhi() const {
        return (Jet1.delta_phi_to(Jet2));
    }

    inline float GetPairDeltaRap() const {
        return (std::abs(Jet1.rap() - Jet2.rap()));
    }

    inline float GetPairDeltaR() const {
        return (Jet1.delta_R(Jet2));
    }

    inline float GetTripleDeltaPhi() const {
        return (Jet3.delta_phi_to(GetPairJet()));
    }

    inline float GetTripleDeltaRap() const {
        return (std::abs(Jet3.rap() - GetPairJet().rap()));
    }

    inline float GetTripleDeltaR() const {
        return (Jet3.delta_R(GetPairJet()));
    }

    inline fastjet::PseudoJet GetJet1()const {
        return Jet1;
    }

    inline fastjet::PseudoJet GetJet2()const {
        return Jet2;
    }

    inline fastjet::PseudoJet GetJet3()const {
        return Jet3;
    }

//     inline void SetPair(const HPair &Pair) {
//         Jet2 = Pair.GetJet1();
//         Jet3 = Pair.GetJet2();
//     }
//
//     inline void SetJet1(const fastjet::PseudoJet &Jet){
//       Jet1 = Jet;
//     }

protected:

    fastjet::PseudoJet Jet1;

    fastjet::PseudoJet Jet2;

    fastjet::PseudoJet Jet3;

    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

private:

};

#endif
