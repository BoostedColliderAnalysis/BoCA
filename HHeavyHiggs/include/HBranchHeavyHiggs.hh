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
class HEventLeptonicBranch;
class HEventHadronicBranch;
class HEventSemiBranch;
class HEventLeptonicTagger;
class HEventHadronicTagger;
class HEventSemiTagger;

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
class hheavyhiggs::HEventLeptonicBranch : public HBranch
{

public:

    HEventLeptonicBranch();

    int LeptonNumber;
    int JetNumber;
    int BottomNumber;

    float ScalarHt;
    float HeavyParticleBdt;

    float HeavyHiggsBdt;
    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float BottomSumPt;
    float BottomDeltaPt;

    float BottomDeltaRap;
    float BottomDeltaPhi;
    float BottomDeltaR;

    float HbSumDeltaRap;
    float HbSumDeltaPhi;
    float HbSumDeltaR;

    float HbDeltaDeltaRap;
    float HbDeltaDeltaPhi;
    float HbDeltaDeltaR;

    int EventTag;

private:

  ClassDef(HEventLeptonicBranch, 1)

};




/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HEventHadronicBranch : public HBranch
{

public:

  HEventHadronicBranch();

  int LeptonNumber;
  int JetNumber;
  int BottomNumber;

  float ScalarHt;
  float HeavyParticleBdt;

  float HeavyHiggsBdt;
  float HeavyHiggsMass;
  float HeavyHiggsPt;

  float BottomSumPt;
  float BottomDeltaPt;

  float BottomDeltaRap;
  float BottomDeltaPhi;
  float BottomDeltaR;

  float HbSumDeltaRap;
  float HbSumDeltaPhi;
  float HbSumDeltaR;

  float HbDeltaDeltaRap;
  float HbDeltaDeltaPhi;
  float HbDeltaDeltaR;

  int EventTag;

private:

  ClassDef(HEventHadronicBranch, 1)

};



/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HEventSemiBranch : public HBranch
{

public:

  HEventSemiBranch();

  int LeptonNumber;
  int JetNumber;
  int BottomNumber;

  float ScalarHt;
  float HeavyParticleBdt;

  float HeavyHiggsBdt;
  float HeavyHiggsMass;
  float HeavyHiggsPt;

  float BottomSumPt;
  float BottomDeltaPt;

  float BottomDeltaRap;
  float BottomDeltaPhi;
  float BottomDeltaR;

  float HbSumDeltaRap;
  float HbSumDeltaPhi;
  float HbSumDeltaR;

  float HbDeltaDeltaRap;
  float HbDeltaDeltaPhi;
  float HbDeltaDeltaR;

  int EventTag;

private:

  ClassDef(HEventSemiBranch, 1)

};


# endif
