#pragma once

#include "Multiplet.hh"
#include "Singlet.hh"

namespace analysis {

class Kinematics {

public:

    Kinematics(float pt, float rap, float phi)
    {
        pt_ = pt;
        rap_ = rap;
        phi_ = phi;
    }

    float GetPt() const
    {
        return pt_;
    }
    float GetRap() const
    {
        return rap_;
    }
    float GetPhi() const
    {
        return phi_;
    }

private:

    float pt_;
    float rap_;
    float phi_;
};

class Doublet : public Multiplet<Singlet, Singlet> {

public:

    using Multiplet<Singlet, Singlet>::Multiplet;

    fastjet::PseudoJet SingletJet1() const;

    fastjet::PseudoJet SingletJet2() const;

    Singlet& Singlet1() const;

    Singlet& Singlet2() const;

    float PullAngle1() const;

    float PullAngle2() const;

    float PullAngle() const
    {
        return PullAngle1() * PullAngle2();
    }

    std::vector<Kinematics> Constituents() const;

private:

    std::vector<Kinematics> Constituents(const fastjet::PseudoJet& jet, float jet_ratio, float theta, float shift) const;

    float ReferenceAngle(const fastjet::PseudoJet& jet, const fastjet::PseudoJet& reference_jet) const;

    float Pull(const fastjet::PseudoJet& jet) const;

};

}
