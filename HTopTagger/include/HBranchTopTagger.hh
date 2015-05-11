# pragma once

# include "Branch.hh"


namespace htoptagger{

  class HAnalysis;
  class HCandidateBranch;
  class HJetTag;

}

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class htoptagger::HCandidateBranch : public Branch
{

public:

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float DeltaR;

    float SubJetsDeltaR;
    float Asymmetry;
    float DiPolarity;

    float SubJet1Mass;
    float SubJet1DeltaR;
    float SubJet1Pt;

    float SubJet2Mass;
    float SubJet2Pt;
    float SubJet2DeltaR;

    float ConstRap;
    float ConstPhi;
    float ConstDeltaR;
    float ConstAngle;

    float IsolationRap;
    float IsolationPhi;
    float IsolationDeltaR;
    float IsolationAngle;
    float IsolationPt;

    float HiggsTag;
    float TopTag;

    float TopBdtTag;
    float JetBdtTag;

    float TopCutSigEff;
    float JetCutSigEff;

    HCandidateBranch();

private:


    ClassDef(HCandidateBranch, 1)

};

class HTopHadronBranch : public HPairBranch
{

public:

  HTopHadronBranch();

  float BottomPt;
  float WPt;

  float BBdt;
  float WBdt;

  float Tau1_1;
  float Tau2_1;
  float Tau3_1;
  float Tau21_1;
  float Tau32_1;

  float Tau1_2;
  float Tau2_2;
  float Tau3_2;
  float Tau21_2;
  float Tau32_2;

  float VertexMass;
  float MaxDisplacement;
  float MeanDisplacement;
  float SumDisplacement;
  float Multipliticity;
  float Spread;
  float VertexDeltaR;
  float VertexSpread;
  float EnergyFraction;

  float LeptonPt;

private:

  ClassDef(HTopHadronBranch, 1)

};
