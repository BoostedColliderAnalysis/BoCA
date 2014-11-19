# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "TObject.h"
# include "Rtypes.h"


namespace hhiggscpv
{

class HDiscriminator;
class HJetTag;
class JetHJetTag;
class HAnalysis;
class HBranchDiscriminator;
class HJetDiscriminator;
class HMva;
class HCandidateBranch;
class HBTaggerBranch;
class HLeptonBranch;
class HMvaBTagger;

}

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hhiggscpv::HCandidateBranch : public TObject
{

public:

    float InvMass1;
    float InvMass2;
    float InvMass3;

    float ScalarHt;
    float JetNumber;
    float BottomNumber;
    float VertexNumber;

    float Pull1;
    float Pull2;
    float Pull3;

    float BTag1;
    float BTag2;
    float BTag3;

    float DeltaR1;
    float DeltaR2;
    float DeltaR3;

    float HiggsTag;
    float TopTag;

    float TopBdtTag;
    float JetBdtTag;

    float TopCutSigEff;
    float JetCutSigEff;

    HCandidateBranch();

    virtual ~HCandidateBranch();

private:

    void reset();

    ClassDef(HCandidateBranch, 1)

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
  float JetMass;
  float VertexNumber;
  float Pull;
  float Vertex;
  float DeltaR;
  float BTag;
  float BdtBTag;
  float BCutSigEff;

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
