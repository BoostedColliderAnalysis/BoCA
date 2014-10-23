# ifndef HBranchTopTagger_hh
# define HBranchTopTagger_hh

# include "TObject.h"

/**
 * \class HCandidateBranch
 *
 * \ingroup HDiscriminator
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class HCandidateBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
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

/**
* @brief Class for saving leptons to root
*
*/
class HLeptonBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
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
class HConstituentBranch : public TObject
{

public:

    float Eta;
    float Phi;
    float Pt;
    int Id;

    HConstituentBranch();

    virtual ~HConstituentBranch();

private:

    void reset();

    ClassDef(HConstituentBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
class HJetPropertiesBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
    float Phi;
    float Radius;

    HJetPropertiesBranch();

    virtual ~HJetPropertiesBranch();

private:

    void reset();

    ClassDef(HJetPropertiesBranch, 1)

};


# endif