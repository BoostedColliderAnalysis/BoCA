# ifndef HPairPair_hh
# define HPairPair_hh

# include "HDoublet.hh"
# include "HSextet.hh"
#include "WIMPMASS.h"

class hanalysis::HQuartet : public HTag
{

public:

    HQuartet() {}

    HQuartet(const HDoublet &NewPair1, const HDoublet &NewPair2);

    HQuartet(const HDoublet &NewPair1, const HDoublet &NewPair2, const fastjet::PseudoJet &NewMet);

    void SetMet(const fastjet::PseudoJet &NewMet) {
        Met = NewMet;
    }

    ~HQuartet();

    float GetDeltaR() const {
        return Doublet1.GetDoubletJet().delta_R(Doublet2.GetDoubletJet());
    }

    float GetInvariantMass() const {
        return GetPairJet().m();
    }

    inline float GetMassDifference(const int ParticleMass) const {
        return std::abs(GetInvariantMass() - ParticleMass);
    }

    inline float GetMissDifference(const HParticleId ParticleId) const {
        return std::abs(GetInvariantMass() - GetParticleMass(ParticleId));
    }

    fastjet::PseudoJet GetPairJet() const {
        return (Doublet1.GetDoubletJet() + Doublet2.GetDoubletJet());
    }

    float GetPtSum() const {
        return (Doublet1.GetDoubletJet().pt() + Doublet2.GetDoubletJet().pt());
    }

//     float GetBdt() const {
//         return (Doublet1.GetBdt() * Doublet2.GetBdt());
//     }

//     float GetTag() const {
//         return (Doublet1.GetTag() * Doublet2.GetTag());
//     }

    float GetDeltaRap() const {
        return (std::abs(Doublet1.GetDoubletJet().rap() - Doublet2.GetDoubletJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Doublet1.GetDoubletJet().delta_phi_to(Doublet2.GetDoubletJet()));
    }

    std::vector<HSextet> GetSextets();

    std::vector<HSextet> GetTriplePairs(const float Mass1, const float Mass2, const float Mass3);

    HSextet GetSextet(HJets Neutrinos);

    HDoublet GetDoublet1()const{return Doublet1;}
    HDoublet GetDoublet2()const{return Doublet2;}

protected:

    virtual inline std::string ClassName() const {
        return "HPairPair";
    };

private:

    void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
        return Jet;
    }

    float GetTransverseError(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) const;

    HDoublet Doublet1;

    HDoublet Doublet2;

    fastjet::PseudoJet Met;

    event22 Structure;

};

#endif
