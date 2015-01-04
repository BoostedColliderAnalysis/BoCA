# ifndef HQuartet31_hh
# define HQuartet31_hh

# include "HTriplet.hh"

class hanalysis::HQuartet31 : public HTag
{

public:

    HQuartet31() {}

    HQuartet31(const hanalysis::HTriplet& NewTriplet, const fastjet::PseudoJet& NewSinglet);

    ~HQuartet31();

    inline float GetDeltaR() const {
        return Triplet.GetTripletJet().delta_R(Singlet);
    }

//     float GetInvariantMass() const {
//         return GetQuartetJet().m();
//     }

//     inline float GetMassDifference(const int ParticleMass) const {
//       return std::abs(GetQuartetJet().m() - ParticleMass);
//     }

    inline float GetMassDifference(const HParticleId ParticleId) const {
      return std::abs(GetQuartetJet().m() - GetParticleMass(ParticleId));
    }

    inline fastjet::PseudoJet GetQuartetJet() const {
        return (Triplet.GetTripletJet() + Singlet);
    }

//     inline float GetPtSum() const {
//         return (Triplet.GetTripletJet().pt() + Singlet.pt());
//     }

    inline float GetDeltaPt() const {
      return abs(Triplet.GetTripletJet().pt() - Singlet.pt());
    }

    inline float GetDeltaRap() const {
        return (std::abs(Triplet.GetTripletJet().rap() - Singlet.rap()));
    }

    inline float GetDeltaPhi() const {
        return (Triplet.GetTripletJet().delta_phi_to(Singlet));
    }

    inline HTriplet GetTriplet()const {
        return Triplet;
    }

    inline fastjet::PseudoJet GetSinglet()const {
        return Singlet;
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet31";
    };

private:

    HTriplet Triplet;

    fastjet::PseudoJet Singlet;

};

#endif
