# ifndef HBranchTest_hh
# define HBranchTest_hh

# include "TObject.h"

namespace htest{

  class HAnalysis;
  class HCandidateBranch;
  class HJetTag;

}

/**
 * @brief Class for saving reconstructed candidates to root
 *
 */
class htest::HCandidateBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
    float Phi;
    float Area;

    float SubJetsDeltaR;

    float SubJet1Mass;
    float SubJet1DeltaR;
    float SubJet1Pt;

    float SubJet2Mass;
    float SubJet2Pt;
    float SubJet2DeltaR;

    float ConstEta;
    float ConstPhi;
    float ConstDeltaR;
    float ConstAngle;

    float IsolationEta;
    float IsolationPhi;
    float IsolationDeltaR;
    float IsolationAngle;
    float IsolationPt;

    float HiggsTag;
    float TopTag;

    float TopBdtTag;
    float JetBdtTag;

    float TopCutSigEff;
    float JetCutSigEff;

    HCandidateBranch();

    virtual ~HCandidateBranch();

private:

    void reset();

    ClassDef(HCandidateBranch, 1)

};

# endif
