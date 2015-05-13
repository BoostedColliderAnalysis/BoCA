# ifndef HBranchHeavyHiggs_hh
# define HBranchHeavyHiggs_hh

# include "Branch.hh"

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
class EventLeptonicBranch;
class EventHadronicBranch;
class EventSemiBranch;
class EventLeptonicTagger;
class EventHadronicTagger;
class EventSemiTagger;
class HChargedeventSemiTagger;
class HChargedLeptonicTagger;
class HChargedHadronicTagger;
class HBdtBranch;
class HChargedSemiBranch;
class HChargedLeptonicBranch;
class HChargedHadronicBranch;
class EventTtSemiBranch;
class EventTtSemiTagger;
class HChargedSignatureSemiTagger;
class HSignatureSemiTagger;
class HChargedOctetBranch;
class HOctetBranch;
}

/**
 * @brief Class for saving leptons to root
 *
 */
class hheavyhiggs::HBranchHeavyHiggs : public Branch
{

public:

    float JetNumber;
    float BTag;
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
class hheavyhiggs::EventLeptonicBranch : public Branch
{

public:

    EventLeptonicBranch();

    float Mass;
    float Pt;
    float Rap;
    float Phi;

    float DeltaPt;
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    float Tag;

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
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
    float RestBTag;
    float ThirdBBdt;

private:

    ClassDef(EventLeptonicBranch, 1)

};




/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::EventHadronicBranch : public Branch
{

public:

    EventHadronicBranch();

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;

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

    float eventTag;

private:

    ClassDef(EventHadronicBranch, 1)

};



/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::EventSemiBranch : public MultiBranch
{

public:

    EventSemiBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
    float ScalarHt;

    float RestNumber;
    float RestHt;
    float RestM;
    float RestPt;
    float RestRap;
    float RestBdt;
    float RestPhi;
    float LeptonHt;

    float HardTopPt;
    float SoftTopPt;

    float MissingEt;

    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float BottomBdt5;
    float BottomBdt6;
    float BottomBdt7;
    float BottomBdt8;
    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;
    float BottomBdt78;

    float SubBottomBdt1;
    float SubBottomBdt2;
    float SubBottomBdt3;
    float SubBottomBdt4;
    float SubBottomBdt5;
    float SubBottomBdt6;
    float SubBottomBdt7;
    float SubBottomBdt8;
    float SubBottomBdt12;
    float SubBottomBdt34;
    float SubBottomBdt56;
    float SubBottomBdt78;


private:

    ClassDef(EventSemiBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::EventTtSemiBranch : public MultiBranch
{

public:

    EventTtSemiBranch();


    float HiggsMass;
    float HiggsBdt;

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
    float ScalarHt;

    float RestNumber;
    float RestHt;
    float RestM;
    float RestPt;
    float RestRap;
    float RestBdt;
    float RestPhi;
    float LeptonHt;

private:

    ClassDef(EventTtSemiBranch, 1)

};

class hheavyhiggs::HBdtBranch : public Branch
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

    float eventTag;

private:

    ClassDef(HBdtBranch, 1)

};



/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HOctetBranch : public MultiBranch
{

public:

    HOctetBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;

private:

    ClassDef(HOctetBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedOctetBranch : public MultiBranch
{

public:

    HChargedOctetBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;

private:

    ClassDef(HChargedOctetBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedSemiBranch : public MultiBranch
{

public:

    HChargedSemiBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
    float ScalarHt;

    float RestNumber;
    float RestHt;
    float RestM;
    float RestPt;
    float RestRap;
    float RestBdt;
    float RestPhi;
    float LeptonHt;
    float MissingEt;

    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float BottomBdt5;
    float BottomBdt6;
    float BottomBdt7;
    float BottomBdt8;
    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;
    float BottomBdt78;

    float SubBottomBdt1;
    float SubBottomBdt2;
    float SubBottomBdt3;
    float SubBottomBdt4;
    float SubBottomBdt5;
    float SubBottomBdt6;
    float SubBottomBdt7;
    float SubBottomBdt8;
    float SubBottomBdt12;
    float SubBottomBdt34;
    float SubBottomBdt56;
    float SubBottomBdt78;

private:

    ClassDef(HChargedSemiBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedLeptonicBranch : public Branch
{

public:

    HChargedLeptonicBranch();

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;

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

    float eventTag;

private:

    ClassDef(HChargedLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HChargedHadronicBranch : public Branch
{

public:

    HChargedHadronicBranch();

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;

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

    float eventTag;

private:

    ClassDef(HChargedHadronicBranch, 1)

};


# endif
