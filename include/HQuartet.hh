# ifndef HQuartet_hh
# define HQuartet_hh

# include "HDoublet.hh"

class hanalysis::HQuartet : public HTag
{

public:

    HQuartet() {}

    HQuartet(const hanalysis::HDoublet &NewDoublet1, const hanalysis::HDoublet &NewDoublet2);

    ~HQuartet();

    inline float GetDeltaR() const {
        return Doublet1.GetDoubletJet().delta_R(Doublet2.GetDoubletJet());
    }

//     float GetInvariantMass() const {
//         return GetPairJet().m();
//     }

//     inline float GetMassDifference(const int ParticleMass) const {
//       return std::abs(GetPairJet().m() - ParticleMass);
//     }

    inline float GetMassDifference(const HParticleId ParticleId) const {
      return std::abs(GetQuartetJet().m() - GetParticleMass(ParticleId));
    }

    inline fastjet::PseudoJet GetQuartetJet() const {
        return (Doublet1.GetDoubletJet() + Doublet2.GetDoubletJet());
    }

//     float GetPtSum() const {
//         return (Doublet1.GetDoubletJet().pt() + Doublet2.GetDoubletJet().pt());
//     }

inline float GetDeltaRap() const {
        return (std::abs(Doublet1.GetDoubletJet().rap() - Doublet2.GetDoubletJet().rap()));
    }

    inline float GetDeltaPhi() const {
        return (Doublet1.GetDoubletJet().delta_phi_to(Doublet2.GetDoubletJet()));
    }

    inline HDoublet GetDoublet1()const {
        return Doublet1;
    }

    inline HDoublet GetDoublet2()const {
        return Doublet2;
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
