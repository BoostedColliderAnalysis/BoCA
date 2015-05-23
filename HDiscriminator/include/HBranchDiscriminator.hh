# ifndef BranchDiscriminator_hh
# define BranchDiscriminator_hh

# include "TObject.h"
# include "Rtypes.h"
# include "TGenericClassInfo.h"

namespace hcpvhiggs{

  class HDiscriminator;
  class JetTag;
  class JetJetTag;
  class HAnalysis;
  class BranchDiscriminator;
  class HJetDiscriminator;
  class HMva;
  class HCandidateBranch;
  class HLeptonBranch;
  class ConstituentBranch;
  class HJetPropertiesBranch;

}

/**
 * \class HCandidateBranch
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hcpvhiggs::HCandidateBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float DeltaR;

    float ScalarHt;

    float SubJetsDeltaR;
    float Asymmetry;
    float DiPolarity;

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

/**
* @brief Class for saving leptons to root
*
*/
class hcpvhiggs::HLeptonBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    int Charge;

    HLeptonBranch();

    virtual ~HLeptonBranch();

private:

    void reset();

    ClassDef(HLeptonBranch, 1)

};

/**
 * @brief Class for saving leptons to root
 *
 */
class hcpvhiggs::ConstituentBranch : public TObject
{

public:

    float Rap;
    float Phi;
    float Pt;
    int Id;

    ConstituentBranch();

    virtual ~ConstituentBranch();

private:

    void reset();

    ClassDef(ConstituentBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
class hcpvhiggs::HJetPropertiesBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float Radius;

    HJetPropertiesBranch();

    virtual ~HJetPropertiesBranch();

private:

    void reset();

    ClassDef(HJetPropertiesBranch, 1)

};


# endif
