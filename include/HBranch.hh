# ifndef HBranch_hh
# define HBranch_hh

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
    HBranch() {};
    virtual ~HBranch() {};

protected:
    static const int InitialValue = -10;

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
    int EventNumber;

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
    int Multipliticity;
    float DeltaR;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;
    int BTag;

    int Tag;
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

  int Tag;
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
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    int Tag;

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

//     float Mass;
//     float Rap;
//     float Phi;
//     float Pt;
//     float Ht;

//     float DeltaPt;
//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;

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
//     float Ht;

//     float Mass;
//     float Pt;
//     float Rap;
//     float Phi;

//     float DeltaPt;
//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

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

//     float Bdt;
//     int Tag;

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

  float DeltaM;

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

//     float Ht;
    float LeptonPt;
    float NeutrinoPt;

//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     int Tag;

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

//     float Ht;

    float BottomPt;
    float WPt;

//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;

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

//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;

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

//     float Ht;
    float BottomPt;
    float WPt;

//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;

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

    int HiggsTag;

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

//     float Mass;
//     float Pt;
//     float Rap;
//     float Phi;

//     float DeltaPt;
//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;


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

//     float LargerWDeltaRap;
//     float LargerWDeltaPhi;
//     float LargerWDeltaR;
//
//     float SmallerWDeltaRap;
//     float SmallerWDeltaPhi;
//     float SmallerWDeltaR;
//
//     float LargerNeutrinoDeltaRap;
//     float LargerNeutrinoDeltaPhi;
//     float LargerNeutrinoDeltaR;
//
//     float SmallerNeutrinoDeltaRap;
//     float SmallerNeutrinoDeltaPhi;
//     float SmallerNeutrinoDeltaR;


    float TopBdt;

    int HeavyHiggsTag;

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

//     float Mass;
//     float Rap;
//     float Phi;
//     float Pt;
//     float Ht;

//     float DeltaPt;
//     float DeltaRap;
//     float DeltaPhi;
//     float DeltaR;

//     float Bdt;
//     int Tag;

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

//     float HeavyHiggsMass;
//     float HeavyHiggsPt;

//     float TopDeltaRap;
//     float TopDeltaPhi;
//     float TopDeltaR;

//     float TopBdt;

//     int HeavyHiggsTag;

    int Flag;

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

    //     float LargerWDeltaRap;
    //     float LargerWDeltaPhi;
    //     float LargerWDeltaR;
    //
    //     float SmallerWDeltaRap;
    //     float SmallerWDeltaPhi;
    //     float SmallerWDeltaR;
    //
    //     float LargerNeutrinoDeltaRap;
    //     float LargerNeutrinoDeltaPhi;
    //     float LargerNeutrinoDeltaR;
    //
    //     float SmallerNeutrinoDeltaRap;
    //     float SmallerNeutrinoDeltaPhi;
    //     float SmallerNeutrinoDeltaR;


    float TopBdt;

    int HeavyHiggsTag;

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

    int HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsLeptonicBranch, 1)

};

# endif
