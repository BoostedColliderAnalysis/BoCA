# pragma once

# include "Multiplet.hh"
# include "Singlet.hh"

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



class Doublet : public Multiplet<Singlet,Singlet>
{

public:

    using Multiplet<Singlet,Singlet>::Multiplet;

    void SetSinglets(const fastjet::PseudoJet &singlet_1, const fastjet::PseudoJet &singlet_2);

    void SetSinglets(const fastjet::PseudoJet &singlet);

    fastjet::PseudoJet Singlet1()const;

    fastjet::PseudoJet Singlet2()const;

    float PullAngle1() const;

    float PullAngle2() const;

    inline float PullAngle() const {
        return PullAngle1() * PullAngle2();
    }

    inline void SetRestJets(const Jets &jets) {
        rest_jets_ = jets;
        std::sort(rest_jets_.begin(), rest_jets_.end(), SortByBdt());
    }

    inline void AddRestJet(const fastjet::PseudoJet &jet) {
        rest_jets_.emplace_back(jet);
        std::sort(rest_jets_.begin(), rest_jets_.end(), SortByBdt());
    }

    Jets RestJets() const {
        return rest_jets_;
    }

    float BdtRatio1(const int number) const {
        if (unsigned(number) > rest_jets_.size()) return 0;
//         return Singlet1().user_info<JetInfo>().Bdt() / rest_jets_.at(number - 1).user_info<JetInfo>().Bdt();
        return SubMultiplet1().Bdt() / rest_jets_.at(number - 1).user_info<JetInfo>().Bdt();
    }

    float BdtRatio2(const int number)const {
        if (unsigned(number) > rest_jets_.size()) return 0;
        return SubMultiplet1().Bdt() / rest_jets_.at(number - 1).user_info<JetInfo>().Bdt();
    }

    std::vector< Kinematics > constituents() const;

    bool overlap() const {
        DetectorGeometry detector_geometry_;
        if (Singlet1().delta_R(Singlet2()) < detector_geometry_.JetConeSize) return true;
        return false;
    }

protected:

    std::vector< Kinematics > constituents(const fastjet::PseudoJet &jet, const float jet_ratio, const float theta, const float shift) const;

    float ReferenceAngle(const fastjet::PseudoJet &jet, const fastjet::PseudoJet &reference_jet) const;

    float Pull(const fastjet::PseudoJet &jet) const;

    virtual inline std::string ClassName() const {
        return "Doublet";
    }

private:

    Jets rest_jets_;

};

}
