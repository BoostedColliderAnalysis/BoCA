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
class HHeavyHiggsBranch;
class HEventBranch;
class HMvaEvent;

}

/**
 * @brief Class for saving leptons to root
 *
 */
class hheavyhiggs::HHeavyHiggsBranch : public HBranch
{

public:

    int JetNumber;
    int BTag;
    float Isolation;

    float BottomEta1;
    float BottomEta2;
    float BottomDeltaEta;
    float BottomSumEta;

    float BottomPhi1;
    float BottomPhi2;
    float BottomDeltaPhi;
    float BottomSumPhi;

    float BottomPt1;
    float BottomPt2;
    float BottomInvMass;
    float BottomDeltaPt;

//     float TopEta1;
//     float TopEta2;
//     float TopDeltaEta;
//
//     float TopPhi1;
//     float TopPhi2;
//     float TopDeltaPhi;
//
//     float TopPt1;
//     float TopPt2;
//     float TopInvMass;

    HHeavyHiggsBranch();

    virtual ~HHeavyHiggsBranch() {};

private:

    ClassDef(HHeavyHiggsBranch, 1)

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
    float DeltaEta;
    float DeltaPhi;
    float DeltaR;

    int Signal;

private:

    ClassDef(HEventBranch, 1)

};

# endif
