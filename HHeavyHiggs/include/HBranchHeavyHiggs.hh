# ifndef HBranchHeavyHiggs_hh
# define HBranchHeavyHiggs_hh

# include "HBranch.hh"

namespace hheavyhiggs
{

class HAnalysisHeavyHiggsDelphes;
class HAnalysisHeavyHiggsPgs;
class HAnalysisHeavyHiggsParton;
class HAnalysisMva;
class HHeavyHiggsJetTag;
class HMva;
class HBranchHeavyHiggs;
class HEventBranch;
class HMvaEvent;

}

/**
 * @brief Class for saving leptons to root
 *
 */
class hheavyhiggs::HBranchHeavyHiggs : public HBranch
{

public:

    int JetNumber;
    int BTag;
    float Isolation;

    float BottomRap1;
    float BottomRap2;
    float BottomDeltaRap;
    float BottomSumRap;

    float BottomPhi1;
    float BottomPhi2;
    float BottomDeltaPhi;
    float BottomSumPhi;

    float BottomPt1;
    float BottomPt2;
    float BottomInvMass;
    float BottomDeltaPt;

//     float TopRap1;
//     float TopRap2;
//     float TopDeltaRap;
//
//     float TopPhi1;
//     float TopPhi2;
//     float TopDeltaPhi;
//
//     float TopPt1;
//     float TopPt2;
//     float TopInvMass;

    HBranchHeavyHiggs();

    virtual ~HBranchHeavyHiggs() {};

private:

    ClassDef(HBranchHeavyHiggs, 1)

};




/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HEventBranch : public HBranch
{

public:

    HEventBranch();

    float ScalarHt;
    int JetNumber;
    int BottomNumber;
    int LeptonNumber;
    float HeavyParticleTag;
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    int Signal;

private:

    ClassDef(HEventBranch, 1)

};

# endif
