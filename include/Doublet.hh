# pragma once

# include "Identification.hh"
# include "JetInfo.hh"

namespace analysis {

class Kinematics
{

public:

    Kinematics(const float pt, const float rap, const float phi) {
        pt_ = pt;
        rap_ = rap;
        phi_ = phi;
    }

    float GetPt() const {
        return pt_;
    }
    float GetRap() const {
        return rap_;
    }
    float GetPhi() const {
        return phi_;
    }

private:

    float pt_;
    float rap_;
    float phi_;
};



class Doublet : public Identification
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

    inline float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - GetParticleMass(particle_id));
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
        rest_jets_ = NewJets;
        std::sort(rest_jets_.begin(), rest_jets_.end(), SortByBdt());
    }

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        rest_jets_.emplace_back(NewJet);
        std::sort(rest_jets_.begin(), rest_jets_.end(), SortByBdt());
    }

    Jets RestJets() const {
        return rest_jets_;
    }

    float BdtRatio1(const int Number) const {
        if (unsigned(Number) > rest_jets_.size()) return 0;
        return singlet_1_.user_info<JetInfo>().Bdt() / rest_jets_.at(Number - 1).user_info<JetInfo>().Bdt();
    }

    float BdtRatio2(const int Number)const {
        if (unsigned(Number) > rest_jets_.size()) return 0;
        return singlet_1_.user_info<JetInfo>().Bdt() / rest_jets_.at(Number - 1).user_info<JetInfo>().Bdt();
    }

    std::vector< Kinematics > constituents() const;

protected:

    void SetSinglet1(const fastjet::PseudoJet &singlet);

    void SetSinglet2(const fastjet::PseudoJet &singlet);

    std::vector< Kinematics > constituents(const fastjet::PseudoJet &jet, const float jet_ratio, const float theta, const float shift) const;

    float ReferenceAngle(const fastjet::PseudoJet &jet, const fastjet::PseudoJet &reference_jet) const;

    float Pull(const fastjet::PseudoJet &jet) const;

    fastjet::PseudoJet singlet_1_;

    fastjet::PseudoJet singlet_2_;

    Jets rest_jets_;

    virtual inline std::string ClassName() const {
        return "Doublet";
    }

private:

};

}
