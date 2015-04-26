# pragma once

# include "TObject.h"
# include "Rtypes.h"
# include "TGenericClassInfo.h"

/**
 * @brief Basic tree branches
 *
 */
class HBranch : public TObject
{

public:
    HBranch();
    virtual ~HBranch();

protected:
    float InitialValue;

private:
    ClassDef(HBranch, 1)

};

/**
 * @brief Basic tree branches
 *
 */
class HInfoBranch : public HBranch
{

public:

    float Crosssection;
    float CrosssectionError;
    float Mass;
    float EventNumber;

    HInfoBranch();

private:

    ClassDef(HInfoBranch, 1)

};

/**
 * @brief Class for saving Event informations to root
 *
 */
class HEventBranch : public HBranch
{

public:

    float ScalarPtSum;
    HEventBranch();

private:
    ClassDef(HEventBranch, 1)

};


class HResultBranch : public HBranch
{
public:

    HResultBranch();

    float Bdt;
    float Tag;

private:

    ClassDef(HResultBranch, 1)

};

/**
 * @brief Class for saving Event informations to root
 *
 */
class HParticleBranch : public HBranch
{
public:

    HParticleBranch();

    float Mass;
    float Pt;
    float Rap;
    float Phi;

private:

    ClassDef(HParticleBranch, 1)

};


/**
 *
 * @brief Bottom tagger root tree structure
 *
 */
class HBottomBranch : public HParticleBranch
{

public:

    HBottomBranch();

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float DeltaR;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;
    float BTag;

    float Tag;
    float Bdt;

private:

    ClassDef(HBottomBranch, 1)

};


/**
 *
 * @brief Tau tagger root tree structure
 *
 */
class HTauBranch : public HParticleBranch
{

public:

    HTauBranch();

    float EmRadius;
    float TrackRadius;
    float MomentumFraction;
    float CoreEnergyFraction;
    float EmFraction;
    float ClusterMass;
    float TrackMass;
    float FlightPath;
    float TrtHtFraction;

    float Tag;
    float Bdt;

private:

    ClassDef(HTauBranch, 1)

};


class HPairBranch : public HParticleBranch
{

public:

    HPairBranch();

    float Ht;
    float DeltaPt;
    float DeltaHt;
    float DeltaM;
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float WBdt;
    float BBdt;
    float Bdt;
    float Tag;

private:

    ClassDef(HPairBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HWBranch : public HPairBranch
{

public:

    HWBranch();

private:

    ClassDef(HWBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HEventJetPairBranch : public HPairBranch
{

public:

    HEventJetPairBranch();

    float DeltaM;

    float Jet1Mass;
    float Jet1Pt;
    float Jet1Rap;
    float Jet1Phi;
    float Jet1Bdt;
    float Jet1BTag;

    float Jet2Mass;
    float Jet2Pt;
    float Jet2Rap;
    float Jet2Phi;
    float Jet2Bdt;
    float Jet2BTag;

    float BdtRatio11;
    float BdtRatio12;
    float BdtRatio13;
    float BdtRatio14;
    float BdtRatio21;
    float BdtRatio22;
    float BdtRatio23;
    float BdtRatio24;

private:

    ClassDef(HEventJetPairBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedJetPairBranch : public HPairBranch
{

public:

    HChargedJetPairBranch();

    float BottomMass;
    float BottomPt;
    float BottomRap;
    float BottomPhi;
    float BottomBdt;
    float BottomBTag;

    float TopMass;
    float TopPt;
    float TopRap;
    float TopPhi;
    float TopBdt;
    float TopBTag;

private:

    ClassDef(HChargedJetPairBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HWSemiBranch : public HPairBranch
{

public:

    HWSemiBranch();

    float LeptonPt;
    float NeutrinoPt;

private:

    ClassDef(HWSemiBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HHeavyHiggsTauBranch : public HPairBranch
{

public:

    HHeavyHiggsTauBranch();

    float LeptonPt;
    float NeutrinoPt;

private:

    ClassDef(HHeavyHiggsTauBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopHadronicBranch : public HPairBranch
{

public:

    HTopHadronicBranch();

    float BottomPt;
    float WPt;

    float Tau1_1;
    float Tau2_1;
    float Tau3_1;
    float Tau21_1;
    float Tau32_1;

    float Tau1_2;
    float Tau2_2;
    float Tau3_2;
    float Tau21_2;
    float Tau32_2;

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;

private:

    ClassDef(HTopHadronicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonicBranch : public HPairBranch
{

public:

    HTopLeptonicBranch();

    float BottomPt;
    float LeptonPt;

private:
    ClassDef(HTopLeptonicBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopSemiBranch : public HPairBranch
{

public:

    HTopSemiBranch();
    float BottomPt;
    float WPt;

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;

private:

    ClassDef(HTopSemiBranch, 1)

};


/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHiggsBranch : public HBranch
{

public:

    HHiggsBranch();

    float Mass;
    float PtSum;
    float PtDiff;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float BottomBdt;

    float Pull1;
    float Pull2;
    float Pull;

    float HiggsTag;

private:

    ClassDef(HHiggsBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsLeptonicBranch : public HPairBranch
{

public:

    HHeavyHiggsLeptonicBranch();

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;


private:

    ClassDef(HHeavyHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsHadronicBranch : public HBranch
{

public:

    HHeavyHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HHeavyHiggsHadronicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsSemiBranch : public HPairBranch
{

public:

    HHeavyHiggsSemiBranch();

private:

    ClassDef(HHeavyHiggsSemiBranch, 1)

};

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class HChargedHiggsSemiBranch : public HPairBranch
{

public:

    HChargedHiggsSemiBranch();
    float Flag;

private:

    ClassDef(HChargedHiggsSemiBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedHiggsHadronicBranch : public HBranch
{

public:

    HChargedHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsHadronicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedHiggsLeptonicBranch : public HBranch
{

public:

    HChargedHiggsLeptonicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsLeptonicBranch, 1)

};

class HEventBottomTaggerBranch : public HBranch
{

public:

    HEventBottomTaggerBranch();

    float Bdt;
    float Tag;

    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float BottomBdt5;
    float BottomBdt6;
    float BottomBdt7;

    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;

    float BottomBdt123;
    float BottomBdt1234;


private:

    ClassDef(HEventBottomTaggerBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonBranch : public HPairBranch
{

public:

    HTopLeptonBranch();

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float DeltaR;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;
    float JetMass;
    float LeptonPt;

private:

    ClassDef(HTopLeptonBranch, 1)

};

