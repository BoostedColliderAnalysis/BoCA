# ifndef HTriplet_hh
# define HTriplet_hh

# include "HDoublet.hh"

class hanalysis::HTriplet : public HTag
{

public:

    HTriplet();

    HTriplet(const hanalysis::HDoublet& NewDoublet, const fastjet::PseudoJet& NewJet);

    ~HTriplet();

    fastjet::PseudoJet GetDoubletJet() const {
        return Doublet.GetDoubletJet();
    }

    fastjet::PseudoJet GetTripletJet() const {
        return (GetDoubletJet() + Jet);
    }

//     inline float GetPairInvariantMass() const {
//         return (GetDoubletJet().m());
//     }

//     inline float GetTripleInvariantMass() const {
//         return (GetTripleJet().m());
//     }

//     inline float GetPairMassDifference(const int ParticleMass) const {
//         return std::abs(GetPairInvariantMass() - ParticleMass);
//     }

    inline float GetJetMassDifference(const HParticleId ParticleId) const {
        return std::abs(Jet.m() - GetParticleMass(ParticleId));
    }

    inline float GetDoubletMassDifference(const HParticleId ParticleId) const {
        return std::abs(GetDoubletJet().m() - GetParticleMass(ParticleId));
    }

//     inline float GetTripleMassDifference(const int ParticleMass) const {
//       return std::abs(GetTripleInvariantMass() - ParticleMass);
//     }

    inline float GetTripleMassDifference(const HParticleId ParticleId) const {
        return std::abs(GetTripletJet().m() - GetParticleMass(ParticleId));
    }

//     inline float GetPairPtSum() const {
//         return (Jet1.pt() + Jet2.pt());
//     }

//     inline float GetPairPtDiff() const {
//         return std::abs(Jet1.pt() - Jet2.pt());
//     }

//     inline float GetTriplePtSum() const {
//         return (Jet3.pt() + GetDoubletJet().pt());
//     }

    inline float GetTriplePtDiff() const {
        return std::abs(Jet.pt() - GetDoubletJet().pt());
    }

//     inline float GetPairDeltaPhi() const {
//         return (Jet1.delta_phi_to(Jet2));
//     }

//     inline float GetPairDeltaRap() const {
//         return (std::abs(Jet1.rap() - Jet2.rap()));
//     }

//     inline float GetPairDeltaR() const {
//         return (Jet1.delta_R(Jet2));
//     }

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

//     inline fastjet::PseudoJet GetJet2()const {
//         return Jet2;
//     }

    inline fastjet::PseudoJet GetJet()const {
        return Jet;
    }

//     inline void SetPair(const HPair &Pair) {
//         Jet2 = Pair.GetJet1();
//         Jet3 = Pair.GetJet2();
//     }
//
//     inline void SetJet1(const fastjet::PseudoJet &Jet){
//       Jet1 = Jet;
//     }

// //     inline void SetJets(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2, const fastjet::PseudoJet &NewJet3) {
//         Jet1 = NewJet1;
//         Jet2 = NewJet2;
//         Jet3 = NewJet3;
//     }

protected:

  HDoublet Doublet;

    fastjet::PseudoJet Jet;

    virtual inline std::string ClassName() const {
        return "HTriple";
    };

private:

};

#endif
