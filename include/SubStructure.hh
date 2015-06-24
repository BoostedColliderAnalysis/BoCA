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

     float GetSubJet1Mass() const {
        return (SubJet1.Mass / Global.Mass);
    }

     float GetSubJet2Mass() const {
        return (SubJet2.Mass / Global.Mass);
    }

     float GetSubJet1Pt() const {
        return (SubJet1.Pt / Global.Pt);
    }

     float GetSubJet2Pt() const {
        return (SubJet2.Pt / Global.Pt);
    }

     float GetSubJet1DeltaR() const {
        return (SubJet1.DeltaR / Global.DeltaR);
    }

     float GetSubJet2DeltaR() const {
        return (SubJet2.DeltaR / Global.DeltaR);
    }

     float GetSubJetsDeltaR() const {
        return Global.DeltaR;
    }

     float GetconstituentRap() const {
        return Global.Rap;
    }

     float GetconstituentPhi() const {
        return Global.Phi;
    }

     float GetconstituentDeltaR() const {
        return Length(Global.Rap, Global.Phi);
    }

     float GetconstituentAngle() const {
        return atan2(Global.Phi, Global.Rap);
    }

     float GetIsolationRap() const {
        return Isolation.Rap;
    }

     float GetIsolationPhi() const {
        return Isolation.Phi;
    }

     float GetIsolationPt() const {
        return Isolation.Pt;
    }

     float GetIsolationDeltaR() const {
        return Isolation.DeltaR;
    }

     float GetIsolationAngle() const {
        return atan2(Isolation.Phi, Isolation.Rap);
    }

     float GetAsymmetry() const {
        return Asymmetry;
    }

     float GetDeltaR() const {
        return DeltaR;
    }

protected:

  virtual  std::string ClassName() const {
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

     float GetPosition2Rap() const {
        return (2 * Shift);
    }

     float GetPosDistance() const {
        return Length(GetPosition2Rap(), 0);
    }

    float SubJetRatio;

    bool SubJets;

};

}
