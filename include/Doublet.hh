# pragma once

# include "HTag.hh"
# include "JetInfo.hh"

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



class hanalysis::Doublet : public HTag
{

public:

    Doublet();

    Doublet(const fastjet::PseudoJet &singlet_1, const fastjet::PseudoJet &singlet_2);

    Doublet(const fastjet::PseudoJet &singlet);

    void SetSinglets(const fastjet::PseudoJet &singlet_1, const fastjet::PseudoJet &singlet_2);

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
        float delta_r = Singlet1().delta_R(Singlet2());
        if (std::abs(delta_r) > 100) delta_r = 0;
        return delta_r;
    }

    fastjet::PseudoJet Singlet1()const;

    fastjet::PseudoJet Singlet2()const;

    float PullAngle1() const;

    float PullAngle2() const;

    inline float PullAngle() const {
        return PullAngle1() * PullAngle2();
    }

    inline void SetRestJets(const Jets &NewJets) {
        RestJetsM = NewJets;
        std::sort(RestJetsM.begin(), RestJetsM.end(), SortByBdt());
    }

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        RestJetsM.emplace_back(NewJet);
        std::sort(RestJetsM.begin(), RestJetsM.end(), SortByBdt());
    }

    Jets RestJets() const {
        return RestJetsM;
    }

    float BdtRatio1(const int Number) const {
        if (unsigned(Number) > RestJetsM.size()) return 0;
        return singlet_1_.user_info<JetInfo>().Bdt() / RestJetsM.at(Number - 1).user_info<JetInfo>().Bdt();
    }

    float BdtRatio2(const int Number)const {
        if (unsigned(Number) > RestJetsM.size()) return 0;
        return singlet_1_.user_info<JetInfo>().Bdt() / RestJetsM.at(Number - 1).user_info<JetInfo>().Bdt();
    }

    std::vector< HKinematics > constituents() const;

protected:

    void SetSinglet1(const fastjet::PseudoJet &NewSinglet);

    void SetSinglet2(const fastjet::PseudoJet &NewSinglet);

    std::vector< HKinematics > constituents(const fastjet::PseudoJet &jet, const float jet_ratio, const float theta, const float shift) const;

    float ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const;

    float Pull(const fastjet::PseudoJet &Jet) const;

    fastjet::PseudoJet singlet_1_;

    fastjet::PseudoJet singlet_2_;

    Jets RestJetsM;

    virtual inline std::string ClassName() const {
        return "Doublet";
    }

private:

};




// /**
//  * @brief thin wrappper around fastjet::PseudoJet to make it behave like a HMultiplet
//  *
//  */
// class hanalysis::HSinglet : public HTag
// {
// public:
//
//     HSinglet(const fastjet::PseudoJet &NewPseudoJet) {
//         PseudoJet = NewPseudoJet;
//     }
//
//     fastjet::PseudoJet Jet() const {
//         return PseudoJet;
//     }
//
//     float Pt()const {
//         return PseudoJet.pt();
//     }
//
//     float Ht()const {
//       return PseudoJet.pt();
//     }
//     float Phi()const {
//         return PseudoJet.phi_std();
//     }
//
//     float Rap()const {
//         return PseudoJet.rap();
//     }
//
//
// private:
//     fastjet::PseudoJet PseudoJet;
// };
//
//
//
//
// /**
//  * @brief generic pair class
//  *
//  */
// template<class TMultiplet>
// class hanalysis::HPair : public HTag
// {
//
// public:
//
//     HPair();
//
//     HPair(const TMultiplet &NewMultiplet1, const TMultiplet &NewMultiplet2);
//
//     HPair(const TMultiplet &NewMultiplet);
//
//     void SetSinglets(const TMultiplet &NewMultiplet1, const TMultiplet &NewMultiplet2);
//
//     void SetSinglets(const TMultiplet &NewMultiplet);
//
//     inline fastjet::PseudoJet Jet() const {
//         return (Singlet1() + Singlet2());
//     }
//
//     inline float MassDifferenceTo(const HParticleId ParticleId) const {
//         return std::abs(Jet().m() - GetParticleMass(ParticleId));
//     }
//
//     inline float DeltaM() const {
//         return (Singlet1().m() - Singlet2().m());
//     }
//
//     inline float Ht() const {
//         return (Singlet1().pt() + Singlet2().pt());
//     }
//
//     inline float DeltaPt() const {
//         return (Singlet1().pt() - Singlet2().pt());
//     }
//
//     inline float DeltaPhi() const {
//         return Singlet1().delta_phi_to(Singlet2());
//     }
//
//     inline float DeltaRap() const {
//         float NewDeltaRap = Singlet1().rap() - Singlet2().rap();
//         if (std::abs(NewDeltaRap) > 100) {
//             NewDeltaRap = 0;
//         }
//         return NewDeltaRap;
//     }
//
//     inline float DeltaR() const {
//         float NewDeltaR = Singlet1().delta_R(Singlet2());
//         if (std::abs(NewDeltaR) > 100) {
//             NewDeltaR = 0;
//         }
//         return NewDeltaR;
//     }
//
//     TMultiplet Singlet1()const;
//
//     TMultiplet Singlet2()const;
//
// protected:
//
//     void SetSinglet1(const TMultiplet &NewSinglet);
//
//     void SetSinglet2(const TMultiplet &NewSinglet);
//
//     TMultiplet Singlet1M;
//
//     TMultiplet Singlet2M;
//
//     virtual inline std::string ClassName() const {
//         return "HPair";
//     }
//
// private:
//
// };
