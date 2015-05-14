# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "Branch.hh"

namespace hhiggscpv
{
class HDiscriminator;
class HBottomTag;
class HPairTag;
class HAnalysis;
class HBranchDiscriminator;
class HJetDiscriminator;
class HMvaevent;
class EventBranch;
// class BottomBranch;
// class HTopBranch;
class HLeptonBranch;
class HMvaBottom;
class HMvaHiggs;
class HMvaTop;
// class HHiggsBranch;
}




/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hhiggscpv::EventBranch : public Branch
{

public:

    EventBranch();

    float ScalarHt;
    float JetNumber;
    float BottomNumber;
    float LeptonNumber;
    float HeavyParticleTag;
    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float Signal;

private:

    ClassDef(EventBranch, 1)

};


/**
 * @brief lepton tree structure
 *
 */
class hhiggscpv::HLeptonBranch : public Branch
{

public:

    HLeptonBranch();

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float Charge;

private:

    ClassDef(HLeptonBranch, 1)

};

# endif
