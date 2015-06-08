# include "HBranchBTagger.hh"

ClassImp(bottom::HBTaggerBranch)

bottom::HBTaggerBranch::HBTaggerBranch()
{
  VertexMass = InitialValue();
  JetMass = InitialValue();
  Pull = InitialValue();
  DeltaR = InitialValue();
  Vertex = InitialValue();
  VertexNumber = InitialValue();
  BTag = InitialValue();
  BdtBTag = InitialValue();
  BCutSigEff = InitialValue();
}
