# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "HBranch.hh"

namespace hhiggscpv
{
class HDiscriminator;
class HBottomTag;
class HPairTag;
class HAnalysis;
class HBranchDiscriminator;
class HJetDiscriminator;
class HMvaEvent;
class HEventBranch;
class HBottomBranch;
class HTopBranch;
class HLeptonBranch;
class HMvaBTagger;
class HMvaPair;
class HHiggsBranch;
}


/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HBottomBranch : public HBranch
{

public:

    HBottomBranch();

    float Mass;
    float VertexMass;
    float Pt;
    float Displacement;
    float Multipliticity;
    float DeltaR;

    int Bottom;

private:

    ClassDef(HBottomBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HHiggsBranch : public HBranch
{

public:

    HHiggsBranch();

    float Mass;
    float Pt;

    float DeltaEta;
    float DeltaPhi;
    float DeltaR;

    float BTag;

    float Pull1;
    float Pull2;
    float Pull;

    int Higgs;

private:

    ClassDef(HHiggsBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HTopBranch : public HBranch
{

public:

    HTopBranch();

    float Mass;
    float Pt;

    float DeltaEta;
    float DeltaPhi;
    float DeltaR;

    float BTag;

    int Top;

private:

    ClassDef(HTopBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HEventBranch : public HBranch
{

public:

    HEventBranch();

    float ScalarHt;
    int JetNumber;
    int BottomNumber;
    int LeptonNumber;
    float HeavyParticleTag;

    int Signal;

private:

    ClassDef(HEventBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
class hhiggscpv::HLeptonBranch : public HBranch
{

public:

    HLeptonBranch();

    float Mass;
    float Pt;
    float Eta;
    float Phi;
    int Charge;

private:

    ClassDef(HLeptonBranch, 1)

};

# endif
