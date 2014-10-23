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
class HSubStructure : public HObject
{

public:

    HSubStructure();

    ~HSubStructure();

    void NewEvent();

    bool GetSubJets(const PseudoJet &);

    bool GetConstituents(const PseudoJet &, ExRootTreeBranch *const);

    bool GetIsolation(const PseudoJet &, const vector<PseudoJet> &);

    float GetDiPolarity(const PseudoJet &CandidateJet) const;

    float GetSubJet1Mass() const {
        return (SubJet1.Mass / Global.Mass);
    };

    float GetSubJet2Mass() const {
        return (SubJet2.Mass / Global.Mass);
    };

    float GetSubJet1Pt() const {
        return (SubJet1.Pt / Global.Pt);
    };

    float GetSubJet2Pt() const {
        return (SubJet2.Pt / Global.Pt);
    };

    float GetSubJet1DeltaR() const {
        return (SubJet1.DeltaR / Global.DeltaR);
    };

    float GetSubJet2DeltaR() const {
        return (SubJet2.DeltaR / Global.DeltaR);
    };

    float GetSubJetsDeltaR() const {
        return Global.DeltaR;
    };

    float GetConstituentEta() const {
        return Global.Eta;
    };

    float GetConstituentPhi() const {
        return Global.Phi;
    };

    float GetConstituentDeltaR() const {
        return GetDistance(Global.Eta, Global.Phi);
    };

    float GetConstituentAngle() const {
        return atan2(Global.Phi, Global.Eta);
    };

    float GetIsolationEta() const {
        return Isolation.Eta;
    };

    float GetIsolationPhi() const {
        return Isolation.Phi;
    };

    float GetIsolationPt() const {
        return Isolation.Pt;
    };

    float GetIsolationDeltaR() const {
        return Isolation.DeltaR;
    };

    float GetIsolationAngle() const {
        return atan2(Isolation.Phi, Isolation.Eta);
    };

    float GetAsymmetry() const {
        return Asymmetry;
    };

    float GetDeltaR() const {
        return DeltaR;
    };

protected:

    virtual string ClassName() const {

        return ("HSubStructure");

    };

private:

    float Asymmetry;

    float DeltaR;

    HMomentum Global;

    HMomentum SubJet1;

    HMomentum SubJet2;

    HMomentum Isolation;

    const float Shift = 1;

    float GetPosition2Eta() const {
        return (2 * Shift);
    };


    float GetPosDistance() const {
        return GetDistance(GetPosition2Eta(), 0);
    };

    float SubJetRatio;

    bool SubJets;

};

#endif

