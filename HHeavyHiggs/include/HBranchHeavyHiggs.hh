# ifndef HBranchHeavyHiggs_hh
# define HBranchHeavyHiggs_hh

# include "TObject.h"
# include "Rtypes.h"

namespace hheavyhiggs{

    class HAnalysisHeavyHiggsDelphes;
    class HAnalysisHeavyHiggsPgs;
    class HAnalysisHeavyHiggsParton;
    class HHeavyHiggsJetTag;
      class HMva;
      class HHeavyHiggsBranch;

}

/**
 * @brief Class for saving leptons to root
 *
 */
class hheavyhiggs::HHeavyHiggsBranch : public TObject
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

    virtual ~HHeavyHiggsBranch();

private:

    void reset();

    ClassDef(HHeavyHiggsBranch, 1)

};

# endif
