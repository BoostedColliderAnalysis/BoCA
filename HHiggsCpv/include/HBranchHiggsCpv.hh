# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "TObject.h"
# include "Rtypes.h"


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
class HBTaggerBranch;
class HLeptonBranch;
class HMvaBTagger;
class HMvaPair;
class HPairBranch;
}


/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HBTaggerBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Displacement;
    float Multipliticity;

    inline HBTaggerBranch() {
        reset();
    }

    inline virtual ~HBTaggerBranch() {};

private:

    void reset();

    ClassDef(HBTaggerBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HPairBranch : public TObject
{

public:

    float Mass;
    float Pt;

    float DeltaEta;
    float DeltaPhi;
    float DeltaR;

    float BTag;

    float Pull1;
    float Pull2;
    float Pull;

    inline HPairBranch(){
      reset();
    };

    inline virtual ~HPairBranch(){};

private:

    void reset();

    ClassDef(HPairBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HEventBranch : public TObject
{

public:

    float ScalarHt;
    float JetNumber;
    float BottomNumber;

    float HiggsTag;

    inline HEventBranch(){
      reset();
    }

    inline virtual ~HEventBranch(){};

private:

    void reset();

    ClassDef(HEventBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
class hhiggscpv::HLeptonBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
    float Phi;
    int Charge;

    HLeptonBranch();

    virtual ~HLeptonBranch();

private:

    void reset();

    ClassDef(HLeptonBranch, 1)

};

# endif
