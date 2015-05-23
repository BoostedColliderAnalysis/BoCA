# ifndef HJetPropertiesBranch_hh
# define HJetPropertiesBranch_hh

# include "TObject.h"
# include "Rtypes.h"
# include "TGenericClassInfo.h"

namespace hjetproperties{

    class HAnalysis;
    class JetTag;
    class HCandidateBranch;
    class ConstituentBranch;
    class HLeptonBranch;

}

/**
 * @brief Class for saving leptons to root
 *
 */
class hjetproperties::HCandidateBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float DeltaR;

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
class hjetproperties::ConstituentBranch : public TObject
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
class hjetproperties::HLeptonBranch : public TObject
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

# endif
