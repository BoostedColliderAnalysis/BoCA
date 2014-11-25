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
// class HBottomBranch;
// class HTopBranch;
class HLeptonBranch;
class HMvaBottom;
class HMvaHiggs;
class HMvaTop;
class HHiggsBranch;
}



/**
 *
 * @brief Higgs tagger root tree structure
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

    float BottomTag;

    float Pull1;
    float Pull2;
    float Pull;

    int HiggsTag;

private:

    ClassDef(HHiggsBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
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
 * @brief lepton tree structure
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
