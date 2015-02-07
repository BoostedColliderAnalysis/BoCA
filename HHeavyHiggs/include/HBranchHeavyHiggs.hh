# ifndef HBranchHeavyHiggs_hh
# define HBranchHeavyHiggs_hh

# include "HBranch.hh"

namespace hheavyhiggs
{

class HAnalysisHeavyHiggsDelphes;
class HAnalysisHeavyHiggsPgs;
class HAnalysisHeavyHiggsParton;
class HAnalysisMva;
class HAnalysisTt;
class HAnalysisTau;
class HAnalysisCharged;
class HHeavyHiggsJetTag;
class HMva;
class HBranchHeavyHiggs;
class HEventLeptonicBranch;
class HEventHadronicBranch;
class HEventSemiBranch;
class HEventLeptonicTagger;
class HEventHadronicTagger;
class HEventSemiTagger;
class HChargedEventSemiTagger;
class HChargedLeptonicTagger;
class HChargedHadronicTagger;
class HBdtBranch;
class HChargedSemiBranch;
class HChargedLeptonicBranch;
class HChargedHadronicBranch;
class HEventTtSemiBranch;
class HEventTtSemiTagger;
class HChargedSignatureSemiTagger;
class HSignatureSemiTagger;
class HChargedOctetBranch;
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

  float Mass;
  float Pt;
  float Rap;
  float Phi;

  float DeltaPt;
  float DeltaRap;
  float DeltaPhi;
  float DeltaR;

  float Bdt;
  int Tag;

    int LeptonNumber;
    int JetNumber;
    int BottomNumber;
    float ScalarHt;

    float HiggsMass;
    float PairRap;

    float DeltaPt1;
    float DeltaR1;
    float DeltaPhi1;
    float DeltaRap1;

    float DeltaPt2;
    float DeltaR2;
    float DeltaPhi2;
    float DeltaRap2;

    float RestHt;
    float RestM;
    float RestPt;
    float RestRap;
    float RestBBdt;
    float MaxBBdt;
    float TotalBBdt;
    float RestPhi;
    int RestBTag;
    float ThirdBBdt;

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

  float Mass;
  float Pt;
  float Rap;
  float Phi;

  float DeltaPt;
  float DeltaRap;
  float DeltaPhi;
  float DeltaR;

  float Bdt;
  int Tag;

  float HiggsMass;
  float PairRap;

  int LeptonNumber;
  int JetNumber;
  int BottomNumber;
  float ScalarHt;

  float DeltaPt1;
  float DeltaR1;
  float DeltaPhi1;
  float DeltaRap1;

  float DeltaPt2;
  float DeltaR2;
  float DeltaPhi2;
  float DeltaRap2;

  float RestHt;
  float RestM;
  float RestPt;
  float RestRap;
  float RestBBdt;
  float MaxBBdt;
  float TotalBBdt;
  float RestPhi;
  int RestBTag;
  float ThirdBBdt;
  float LeptonPt;


private:

  ClassDef(HEventSemiBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HEventTtSemiBranch : public HPairBranch
{

public:

  HEventTtSemiBranch();


  float HiggsMass;
  float HiggsBdt;

  int LeptonNumber;
  int JetNumber;
  int BottomNumber;
  float ScalarHt;

  int RestNumber;
  float RestHt;
  float RestM;
  float RestPt;
  float RestRap;
  float RestBdt;
  float RestPhi;
  float LeptonHt;

private:

  ClassDef(HEventTtSemiBranch, 1)

};

class hheavyhiggs::HBdtBranch : public HBranch
{

public:

  HBdtBranch();

  float Mass;
  float Bdt;
  float Error;
  float Rarity;

  float Probability01;
  float Probability02;
  float Probability03;
  float Probability04;
  float Probability05;
  float Probability06;
  float Probability07;
  float Probability08;
  float Probability09;
  float Probability10;

  int EventTag;

private:

  ClassDef(HBdtBranch, 1)

};



/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedOctetBranch : public HPairBranch
{

public:

  HChargedOctetBranch();

  float HiggsMass;
  float PairRap;

private:

  ClassDef(HChargedOctetBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedSemiBranch : public HPairBranch
{

public:

  HChargedSemiBranch();

  float HiggsMass;
  float PairRap;

  int LeptonNumber;
  int JetNumber;
  int BottomNumber;
  float ScalarHt;

  int RestNumber;
  float RestHt;
  float RestM;
  float RestPt;
  float RestRap;
  float RestBdt;
  float RestPhi;
  float LeptonHt;

private:

  ClassDef(HChargedSemiBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedLeptonicBranch : public HBranch
{

public:

  HChargedLeptonicBranch();

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

  ClassDef(HChargedLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedHadronicBranch : public HBranch
{

public:

  HChargedHadronicBranch();

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

  ClassDef(HChargedHadronicBranch, 1)

};


# endif
