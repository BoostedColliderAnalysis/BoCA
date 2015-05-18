# ifndef BranchTest_hh
# define BranchTest_hh

# include "TObject.h"
# include "Rtypes.h"
# include "TGenericClassInfo.h"

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
    float Rap;
    float Phi;
    float Area;

    float SubJetsDeltaR;

    float SubJet1Mass;
    float SubJet1DeltaR;
    float SubJet1Pt;

    float SubJet2Mass;
    float SubJet2Pt;
    float SubJet2DeltaR;

    float ConstRap;
    float ConstPhi;
    float ConstDeltaR;
    float ConstAngle;

    float IsolationRap;
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
