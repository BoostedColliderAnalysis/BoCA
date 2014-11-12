# ifndef HSubStructure_hh
# define HSubStructure_hh

# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HObject.hh"
# include "HBranch.hh"

struct HMomentum {

    float Pt;

    float Mass;

    float Eta;

    float Phi;

    float DeltaR;

};

/**
 * @brief subjet and constituent calculations
 *
 */
class hdelphes::HSubStructure : public hanalysis::HObject
{

public:

    HSubStructure();

    ~HSubStructure();

    void NewEvent();

    bool GetSubJets(const PseudoJet &);

    std::vector< TLorentzVector > GetConstituents(const PseudoJet &CandidateJet);

    bool GetIsolation(const PseudoJet &, const HJets &);

    float GetDiPolarity(const PseudoJet &CandidateJet) const;

    inline float GetSubJet1Mass() const {
        return (SubJet1.Mass / Global.Mass);
    };

    inline float GetSubJet2Mass() const {
        return (SubJet2.Mass / Global.Mass);
    };
    inline
    float GetSubJet1Pt() const {
        return (SubJet1.Pt / Global.Pt);
    };

    inline float GetSubJet2Pt() const {
        return (SubJet2.Pt / Global.Pt);
    };

    inline float GetSubJet1DeltaR() const {
        return (SubJet1.DeltaR / Global.DeltaR);
    };

    inline float GetSubJet2DeltaR() const {
        return (SubJet2.DeltaR / Global.DeltaR);
    };

    inline float GetSubJetsDeltaR() const {
        return Global.DeltaR;
    };

    inline float GetConstituentEta() const {
        return Global.Eta;
    };

    inline float GetConstituentPhi() const {
        return Global.Phi;
    };

    inline float GetConstituentDeltaR() const {
        return GetDistance(Global.Eta, Global.Phi);
    };

    inline float GetConstituentAngle() const {
        return atan2(Global.Phi, Global.Eta);
    };

    inline float GetIsolationEta() const {
        return Isolation.Eta;
    };

    inline float GetIsolationPhi() const {
        return Isolation.Phi;
    };

    inline float GetIsolationPt() const {
        return Isolation.Pt;
    };

    inline float GetIsolationDeltaR() const {
        return Isolation.DeltaR;
    };

    inline float GetIsolationAngle() const {
        return atan2(Isolation.Phi, Isolation.Eta);
    };

    inline float GetAsymmetry() const {
        return Asymmetry;
    };

    inline float GetDeltaR() const {
        return DeltaR;
    };

protected:

  virtual inline std::string ClassName() const {
    return "HSubStructure";
  };

  virtual inline std::string NameSpaceName() const {
    return "HDelphes";
  };

private:

    float Asymmetry;

    float DeltaR;

    HMomentum Global;

    HMomentum SubJet1;

    HMomentum SubJet2;

    HMomentum Isolation;

    const float Shift = 1;

    inline float GetPosition2Eta() const {
        return (2 * Shift);
    };


    inline float GetPosDistance() const {
        return GetDistance(GetPosition2Eta(), 0);
    };

    float SubJetRatio;

    bool SubJets;

};

#endif

