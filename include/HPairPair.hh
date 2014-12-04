# ifndef HPairPair_hh
# define HPairPair_hh

# include "HJetLeptonPair.hh"
# include "HTriplePair.hh"
# include "WIMPMASS.h"

class hanalysis::HPairPair : public HTag
{

public:

    HPairPair() {}

    HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2);

    HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const fastjet::PseudoJet &NewMet);

    void SetMet(const fastjet::PseudoJet &NewMet) {
        Met = NewMet;
    }

    ~HPairPair();

    float GetDeltaR() const {
        return Pair1.GetPairJet().delta_R(Pair2.GetPairJet());
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
        return (Pair1.GetPairJet() + Pair2.GetPairJet());
    }

    float GetPtSum() const {
        return (Pair1.GetPtSum() + Pair2.GetPtSum());
    }

    float GetBdt() const {
        return (Pair1.GetBdt() * Pair2.GetBdt());
    }

    float GetTag() const {
        return (Pair1.GetTag() * Pair2.GetTag());
    }

    float GetDeltaRap() const {
        return (std::abs(Pair1.GetPairJet().rap() - Pair2.GetPairJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Pair1.GetPairJet().delta_phi_to(Pair2.GetPairJet()));
    }

    std::vector<HTriplePair> GetTriplePairs() const;
    
    HTriplePair GetTriplePair() const;

protected:

    virtual inline std::string ClassName() const {
        return "HPairPair";
    };

private:


    HJetLeptonPair Pair1;

    HJetLeptonPair Pair2;

    fastjet::PseudoJet Met;

};

#endif
