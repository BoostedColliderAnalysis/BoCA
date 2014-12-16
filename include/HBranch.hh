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

/**
 * @brief Class for saving Event informations to root
 *
 */
class HParticleBranch : public HBranch
{
public:

    float Pt;
    float Rap;
    float Phi;

    HParticleBranch();

private:
    ClassDef(HParticleBranch, 1)

};


/**
 *
 * @brief Bottom tagger root tree structure
 *
 */
class HBottomBranch : public HBranch
{

public:

    HBottomBranch();

    float Mass;
    float VertexMass;
    float Pt;
    float Displacement;
    int Multipliticity;
    float DeltaR;
    float Spread;
    float EnergyFraction;

    int BottomTag;

private:

    ClassDef(HBottomBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HWBranch : public HBranch
{

public:

    HWBranch();

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

    int WTag;

private:

    ClassDef(HWBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopHadronicBranch : public HBranch
{

public:

    HTopHadronicBranch();

    float Mass;
    float JetPt;
    float WPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float WBottomBdt;

    int TopTag;

private:

    ClassDef(HTopHadronicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonicBranch : public HBranch
{

public:

    HTopLeptonicBranch();

    float Mass;
    float JetPt;
    float LeptonPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float BottomBdt;

    int TopTag;

private:

    ClassDef(HTopLeptonicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopSemiBranch : public HBranch
{

public:

    HTopSemiBranch();

    float Mass;
    float PairMass;

    float TriplePt;
    float PairPt;

    float JetPt;
    float LeptonPt;
    float MissingEt;

    float PairDeltaRap;
    float PairDeltaPhi;
    float PairDeltaR;

    float TripleDeltaRap;
    float TripleDeltaPhi;
    float TripleDeltaR;

    float BottomBdt;

    int TopTag;

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
class HHeavyHiggsLeptonicBranch : public HBranch
{

public:

    HHeavyHiggsLeptonicBranch();

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
class HHeavyHiggsSemiBranch : public HBranch
{

public:

    HHeavyHiggsSemiBranch();

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

    ClassDef(HHeavyHiggsSemiBranch, 1)

};

# endif
