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

class HDoubletPrivate;

/**
 * @brief doublet of two fastjet::PseudoJet
 *
 */
class hanalysis::HDoublet : public HTag
{

public:

  HDoublet();

//   HDoublet(const HDoublet &NewDoublet);

//   HDoublet(HDoublet &&NewDoublet);

//   HDoublet& operator=(HDoublet NewDoublet); //note: pass by value and let compiler do the magics

    HDoublet(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2);

    HDoublet(const fastjet::PseudoJet &NewSinglet);

//     HDoublet(HDoublet && NewDoublet);

//     HDoublet(const HDoublet &NewDoublet);

    ~HDoublet();

    void SetSinglets(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2);

    void SetSinglets(const fastjet::PseudoJet &NewSinglet);

    inline fastjet::PseudoJet Jet() const {
        return (Singlet1() + Singlet2());
    }

    inline float MassDifferenceTo(const HParticleId ParticleId) const {
        return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float DeltaM() const {
        return (Singlet1().m() - Singlet2().m());
    }

    inline float Ht() const {
        return (Singlet1().pt() + Singlet2().pt());
    }

    inline float DeltaPt() const {
        return (Singlet1().pt() - Singlet2().pt());
    }

    inline float DeltaPhi() const {
        return Singlet1().delta_phi_to(Singlet2());
    }

    inline float DeltaRap() const {
        float NewDeltaRap = Singlet1().rap() - Singlet2().rap();
        if (std::abs(NewDeltaRap) > 100) {
            NewDeltaRap = 0;
        }
        return NewDeltaRap;
    }

    inline float DeltaR() const {
        float NewDeltaR = Singlet1().delta_R(Singlet2());
        if (std::abs(NewDeltaR) > 100) {
            NewDeltaR = 0;
        }
        return NewDeltaR;
    }

    fastjet::PseudoJet Singlet1()const;

    fastjet::PseudoJet Singlet2()const;

    float PullAngle1() const;

    float PullAngle2() const;

    inline float PullAngle() const {
        return PullAngle1() * PullAngle2();
    }

    std::vector< HKinematics > Constituents() const;

protected:

//     HDoublet(HDoubletPrivate &NewDoubletPrivate);

//     std::unique_ptr<HDoubletPrivate> DoubletPrivate;

  void SetSinglet1(const fastjet::PseudoJet &NewSinglet);

  void SetSinglet2(const fastjet::PseudoJet &NewSinglet);

  std::vector< HKinematics > Constituents(const fastjet::PseudoJet &NewJet, const float JetRatio, const float Theta, const float Shift) const;

  float ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const;

  float Pull(const fastjet::PseudoJet &Jet) const;

  fastjet::PseudoJet Singlet1M;

  fastjet::PseudoJet Singlet2M;

    virtual inline std::string ClassName() const {
        return "HDoublet";
    }

private:

};

#endif
