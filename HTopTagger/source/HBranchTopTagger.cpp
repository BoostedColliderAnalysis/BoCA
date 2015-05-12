# include "HBranchTopTagger.hh"

ClassImp(htoptagger::HCandidateBranch)

htoptagger::HCandidateBranch::HCandidateBranch()
{
  Mass = InitialValue();
  Pt = InitialValue();
  Rap = InitialValue();
  Phi = InitialValue();

  DeltaR = InitialValue();
  SubJetsDeltaR = InitialValue();
  Asymmetry = InitialValue();
  DiPolarity = InitialValue();

  SubJet1Mass = InitialValue();
  SubJet1Pt = InitialValue();
  SubJet1DeltaR = InitialValue();

  SubJet2Mass = InitialValue();
  SubJet2Pt = InitialValue();
  SubJet2DeltaR = InitialValue();

  ConstRap = InitialValue();
  ConstPhi = InitialValue();
  ConstDeltaR = InitialValue();
  ConstAngle = InitialValue();

  IsolationRap = InitialValue();
  IsolationPhi = InitialValue();
  IsolationDeltaR = InitialValue();
  IsolationAngle = InitialValue();
  IsolationPt = InitialValue();

  HiggsTag = InitialValue();
  TopTag = InitialValue();

  TopBdtTag = InitialValue();
  JetBdtTag = InitialValue();

  TopCutSigEff = InitialValue();
  JetCutSigEff = InitialValue();
}


ClassImp(HTopHadronBranch)

HTopHadronBranch::HTopHadronBranch()
{

  BottomPt = InitialValue();
  WPt = InitialValue();

  BBdt = InitialValue();
  WBdt = InitialValue();

  Tau1_1 = InitialValue();
  Tau2_1 = InitialValue();
  Tau3_1 = InitialValue();
  Tau21_1 = InitialValue();
  Tau32_1 = InitialValue();

  Tau1_2 = InitialValue();
  Tau2_2 = InitialValue();
  Tau3_2 = InitialValue();
  Tau21_2 = InitialValue();
  Tau32_2 = InitialValue();

  VertexMass = InitialValue();
  MaxDisplacement = InitialValue();
  MeanDisplacement = InitialValue();
  SumDisplacement = InitialValue();
  Multipliticity = int(InitialValue());
  Spread = InitialValue();
  VertexDeltaR = InitialValue();
  VertexSpread = InitialValue();
  EnergyFraction = InitialValue();

  LeptonPt = InitialValue();

}


