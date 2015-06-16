# include "HBranchBTagger.hh"

ClassImp(analysis::bottom::HBTaggerBranch)

analysis::bottom::HBTaggerBranch::HBTaggerBranch()
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
