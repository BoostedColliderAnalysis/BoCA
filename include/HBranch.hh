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
    float Centrality;
    float EnergyFraction;

    float BottomTag;

private:

    ClassDef(HBottomBranch, 1)

};

/**
 * 
 * @brief Higgs tagger root tree structure
 *
 */
class HHadronicWBranch : public HBranch
{
    
public:
    
    HHadronicWBranch();
    
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
    
    float WTag;
    
private:
    
    ClassDef(HHadronicWBranch, 1)
    
};

/**
 * 
 * @brief Top tagger root tree structure
 *
 */
class HHadronicTopBranch : public HBranch
{
    
public:
    
    HHadronicTopBranch();
    
    float Mass;
    float JetPt;
    float WPt;
    
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;
    
    float WBottomBdt;
    
    float TopTag;
    
private:
    
    ClassDef(HHadronicTopBranch, 1)
    
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HLeptonicTopBranch : public HBranch
{

public:

    HLeptonicTopBranch();

    float Mass;
    float JetPt;
    float LeptonPt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float BottomBdt;

    float TopTag;

private:

    ClassDef(HLeptonicTopBranch, 1)

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
class HHeavyHiggsBranch : public HBranch
{

public:

    HHeavyHiggsBranch();

    float Mass;
    float Pt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float TopBdt;

    float Pull1;
    float Pull2;
    float Pull;

    float HeavyHiggsTag;

private:

    ClassDef(HHeavyHiggsBranch, 1)

};

# endif
