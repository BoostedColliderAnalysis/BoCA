# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "TObject.h"



namespace hhiggscpv
{

class HDiscriminator;
class HJetTag;
class JetHJetTag;
class HAnalysis;
class HBranchDiscriminator;
class HJetDiscriminator;
class HMva;
class HCandidateBranch;
class HLeptonBranch;

}

/**
 * \class HCandidateBranch
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HCandidateBranch : public TObject
{

public:

    float InvMass1;
    float InvMass2;
    float InvMass3;
    float InvMass4;
    float InvMass5;
    float ScalarHt;

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
class hhiggscpv::HLeptonBranch : public TObject
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

# endif
