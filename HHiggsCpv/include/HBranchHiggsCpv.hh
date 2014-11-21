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
class hhiggscpv::HEventBranch : public TObject
{

public:

    float ScalarHt;
    float JetNumber;
    float BottomNumber;

    float HiggsTag;
//     float TopTag;

//     float TopBdtTag;
//     float JetBdtTag;

//     float TopCutSigEff;
//     float JetCutSigEff;

    HEventBranch();

    virtual ~HEventBranch();

private:

    void reset();

    ClassDef(HEventBranch, 1)

};

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HPairBranch : public TObject
{

public:

    float InvMass;

//     float VertexNumber;

    float Pull1;
    float Pull2;
    float Pull;

    float BTag;

    float DeltaR;

//     float HiggsTag;
//     float TopTag;

    HPairBranch();

    virtual ~HPairBranch();

private:

    void reset();

    ClassDef(HPairBranch, 1)

};


/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HBTaggerBranch : public TObject
{

public:

  float VertexMass;
//   float JetMass;
  float VertexNumber;
//   float Pull;
  float Vertex;
//   float DeltaR;
//   float BTag;
//   float BdtBTag;
//   float BCutSigEff;

  HBTaggerBranch();

  virtual ~HBTaggerBranch();

private:

  void reset();

  ClassDef(HBTaggerBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
// class hhiggscpv::HConstituentBranch : public TObject
// {
//
// public:
//
//   float Eta;
//   float Phi;
//   float Pt;
//   int Id;
//
//   HConstituentBranch();
//
//   virtual ~HConstituentBranch();
//
// private:
//
//   void reset();
//
//   ClassDef(HConstituentBranch, 1)
//
// };




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
