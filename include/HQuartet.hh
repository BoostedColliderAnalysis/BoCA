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
        return Pair1.GetDoubletJet().delta_R(Pair2.GetDoubletJet());
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
        return (Pair1.GetDoubletJet() + Pair2.GetDoubletJet());
    }

    float GetPtSum() const {
        return (Pair1.GetDoubletJet().pt() + Pair2.GetDoubletJet().pt());
    }

    float GetBdt() const {
        return (Pair1.GetBdt() * Pair2.GetBdt());
    }

    float GetTag() const {
        return (Pair1.GetTag() * Pair2.GetTag());
    }

    float GetDeltaRap() const {
        return (std::abs(Pair1.GetDoubletJet().rap() - Pair2.GetDoubletJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Pair1.GetDoubletJet().delta_phi_to(Pair2.GetDoubletJet()));
    }

    std::vector<HSextet> GetTriplePairs();

    std::vector<HSextet> GetTriplePairs(const float Mass1, const float Mass2, const float Mass3);

    HSextet GetTriplePair(HJets Neutrinos);

    HDoublet GetPair1()const{return Pair1;}
    HDoublet GetPair2()const{return Pair2;}

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

    HDoublet Pair1;

    HDoublet Pair2;

    fastjet::PseudoJet Met;

    event22 Structure;

};

#endif
