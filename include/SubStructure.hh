# pragma once

# include "Object.hh"

namespace analysis {

struct Momentum {
    float Pt;
    float Mass;
    float Rap;
    float Phi;
    float DeltaR;
};

/**
 * @brief subjet and constituent calculations
 *
 */
class SubStructure : public Object
{

public:

    SubStructure();

    void NewEvent();

    bool GetSubJets(const fastjet::PseudoJet &);

    std::vector< TLorentzVector > Getconstituents(const fastjet::PseudoJet &CandidateJet);

    bool GetIsolation(const fastjet::PseudoJet& CandidateJet, const Jets& LeptonJets);

    float GetDiPolarity(const fastjet::PseudoJet &CandidateJet) const;

    inline float GetSubJet1Mass() const {
        return (SubJet1.Mass / Global.Mass);
    }

    inline float GetSubJet2Mass() const {
        return (SubJet2.Mass / Global.Mass);
    }

    inline float GetSubJet1Pt() const {
        return (SubJet1.Pt / Global.Pt);
    }

    inline float GetSubJet2Pt() const {
        return (SubJet2.Pt / Global.Pt);
    }

    inline float GetSubJet1DeltaR() const {
        return (SubJet1.DeltaR / Global.DeltaR);
    }

    inline float GetSubJet2DeltaR() const {
        return (SubJet2.DeltaR / Global.DeltaR);
    }

    inline float GetSubJetsDeltaR() const {
        return Global.DeltaR;
    }

    inline float GetconstituentRap() const {
        return Global.Rap;
    }

    inline float GetconstituentPhi() const {
        return Global.Phi;
    }

    inline float GetconstituentDeltaR() const {
        return Distance(Global.Rap, Global.Phi);
    }

    inline float GetconstituentAngle() const {
        return atan2(Global.Phi, Global.Rap);
    }

    inline float GetIsolationRap() const {
        return Isolation.Rap;
    }

    inline float GetIsolationPhi() const {
        return Isolation.Phi;
    }

    inline float GetIsolationPt() const {
        return Isolation.Pt;
    }

    inline float GetIsolationDeltaR() const {
        return Isolation.DeltaR;
    }

    inline float GetIsolationAngle() const {
        return atan2(Isolation.Phi, Isolation.Rap);
    }

    inline float GetAsymmetry() const {
        return Asymmetry;
    }

    inline float GetDeltaR() const {
        return DeltaR;
    }

protected:

  virtual inline std::string ClassName() const {
    return "SubStructure";
  }

private:

    float Asymmetry;

    float DeltaR;

    Momentum Global;

    Momentum SubJet1;

    Momentum SubJet2;

    Momentum Isolation;

    const float Shift = 1;

    inline float GetPosition2Rap() const {
        return (2 * Shift);
    }

    inline float GetPosDistance() const {
        return Distance(GetPosition2Rap(), 0);
    }

    float SubJetRatio;

    bool SubJets;

};

}
