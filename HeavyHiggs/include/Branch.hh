# pragma once

# include "Branches.hh"

namespace heavyhiggs {

/**
 * @brief Class for saving leptons to root
 *
 */
class BranchHeavyHiggs : public analysis::Branch
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

    BranchHeavyHiggs();

private:

    ClassDef(BranchHeavyHiggs, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventNeutralBranch : public analysis::MultiBranch
{

public:

    EventNeutralBranch();

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

    ClassDef(EventNeutralBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusionBranch : public analysis::MultiBranch
{

public:

    EventFusionBranch();


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

    ClassDef(EventFusionBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutralBranch : public analysis::MultiBranch
{

public:

    OctetNeutralBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;

private:

    ClassDef(OctetNeutralBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetChargedBranch : public analysis::MultiBranch
{

public:

    OctetChargedBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;

private:

    ClassDef(OctetChargedBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventChargedBranch : public analysis::MultiBranch
{

public:

    EventChargedBranch();

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

    ClassDef(EventChargedBranch, 1)

};

}
