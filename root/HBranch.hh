# ifndef HBranch_hh
# define HBranch_hh

# include "TObject.h"

/**
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

// ClassImp(HCandidateBranch);

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

// ClassImp(HLeptonBranch);

/**
 * @brief Class for saving leptons to root
 *
 */
class HInfoBranch : public TObject
{

public:

    float Crosssection;    
    float Error;
    float EventNumber;

    HInfoBranch();

    virtual ~HInfoBranch();
    
private:
    
    void reset();

    ClassDef(HInfoBranch, 1)

};

// ClassImp(HInfoBranch);

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
    
    HConstituentBranch();
    
    virtual ~HConstituentBranch();
    
private:
    
    void reset();
    
    ClassDef(HConstituentBranch, 1)
    
};

// ClassImp(HConstituentBranch);

/**
 * @brief Class for saving leptons to root
 *
 */
class HHeavyHiggsBranch : public TObject
{
    
public:
    
    int JetNumber;
    
    float BottomEtaMax;    
    float BottomEtaMin;
    
    float BottomDeltaEta;
    float BottomInvMass;
    
    float TopEtaMax;    
    float TopEtaMin;
    
    float TopDeltaEta;
    float TopInvMass;
    
    float DeltaEta3;
    float BMass3;
    
    float TMass;
    float DeltaPhi;
    int BTag;
    
    HHeavyHiggsBranch();
    
    virtual ~HHeavyHiggsBranch();
    
private:
    
    void reset();
    
    ClassDef(HHeavyHiggsBranch, 1)
    
};

// ClassImp(HHeavyHiggsBranch);

# endif
