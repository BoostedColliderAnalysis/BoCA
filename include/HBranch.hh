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
    float Displacement;
    int Multipliticity;
    float DeltaR;
    float Spread;
    float EnergyFraction;

    int Tag;

private:

    ClassDef(HBottomBranch, 1)

};

class HPairBranch : public HParticleBranch
{

public:

  HPairBranch();

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

    HWBranch();

private:

    ClassDef(HWBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HJetPairBranch : public HPairBranch
{

public:

  HJetPairBranch();

private:

  ClassDef(HJetPairBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HWSemiBranch : public HParticleBranch
{

public:

  HWSemiBranch();

  float LeptonPt;
  float NeutrinoPt;

  float DeltaRap;
  float DeltaPhi;
  float DeltaR;

  int Tag;

private:

  ClassDef(HWSemiBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopHadronicBranch : public HParticleBranch
{

public:

    HTopHadronicBranch();

    float BottomPt;
    float WPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    int Tag;

private:

    ClassDef(HTopHadronicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonicBranch : public HParticleBranch
{

public:

    HTopLeptonicBranch();

    float BottomPt;
    float LeptonPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    int Tag;

private:

    ClassDef(HTopLeptonicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopSemiBranch : public HParticleBranch
{

public:

    HTopSemiBranch();

    float BottomPt;
    float WPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    int Tag;

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

private:

    ClassDef(HHeavyHiggsSemiBranch, 1)

};

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class HChargedHiggsSemiBranch : public HBranch
{

public:

  HChargedHiggsSemiBranch();

  float HeavyHiggsMass;
  float HeavyHiggsPt;

  float TopDeltaRap;
  float TopDeltaPhi;
  float TopDeltaR;

  float TopBdt;

  int HeavyHiggsTag;

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
