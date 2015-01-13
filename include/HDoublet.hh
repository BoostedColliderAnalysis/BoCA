# ifndef HDoublet_hh
# define HDoublet_hh

# include "HTag.hh"
# include "HJetInfo.hh"

class HKinematics
{

public:

    HKinematics(const float NewPt, const float NewRap, const float NewPhi) {
        Pt = NewPt;
        Rap = NewRap;
        Phi = NewPhi;
    }

    float GetPt() const {
        return Pt;
    }
    float GetRap() const {
        return Rap;
    }
    float GetPhi() const {
        return Phi;
    }

private:

    float Pt;
    float Rap;
    float Phi;
};

/**
 * @brief doublet of two fastjet::PseudoJet
 *
 */
class hanalysis::HDoublet : public HTag
{

public:

    HDoublet();

    HDoublet(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

    ~HDoublet();

    void SetJets(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

    fastjet::PseudoJet GetDoubletJet() const {
        return (Jet1 + Jet2);
    }

    inline float GetMassDiffTo(const HParticleId ParticleId) const {
        return std::abs(GetDoubletJet().m() - GetParticleMass(ParticleId));
    }

    inline float GetHt() const {
        return (Jet1.pt() + Jet2.pt());
    }

    inline float GetDeltaM() const {
        return std::abs(Jet1.m() - Jet2.m());
    }

    inline float GetDeltaPt() const {
        return std::abs(Jet1.pt() - Jet2.pt());
    }

    inline float GetDeltaPhi() const {
        return (Jet1.delta_phi_to(Jet2));
    }

    inline float GetDeltaRap() const {
        return (std::abs(Jet1.rap() - Jet2.rap()));
    }

    inline float GetDeltaR() const {
        return (Jet1.delta_R(Jet2));
    }

    fastjet::PseudoJet GetJet1()const {
        return Jet1;
    }

    fastjet::PseudoJet GetJet2()const {
        return Jet2;
    }

    float GetPullAngle1() const;

    float GetPullAngle2() const;

    float GetPullAngle() const {
        return (GetPullAngle1() * GetPullAngle2());
    }

    std::vector< HKinematics > GetConstituents() const;

protected:

    virtual inline std::string ClassName() const {
        return "HDoublet";
    };

private:

    std::vector< HKinematics > GetConstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const;

    float GetReferenceAngle(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &ReferenceJet) const;

    float GetPull(const fastjet::PseudoJet &Jet) const;

    fastjet::PseudoJet Jet1;

    fastjet::PseudoJet Jet2;

};

#endif
