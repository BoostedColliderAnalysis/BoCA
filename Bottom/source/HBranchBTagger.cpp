# include "HBranchBTagger.hh"

ClassImp(bottom::HBTaggerBranch)

bottom::HBTaggerBranch::HBTaggerBranch()
{

    reset();

}

bottom::HBTaggerBranch::~HBTaggerBranch() {}

void bottom::HBTaggerBranch::reset()
{

    const int InitialValue = -10;

    VertexMass = InitialValue;
    JetMass = InitialValue;
    Pull = InitialValue;
    DeltaR = InitialValue;
    Vertex = InitialValue;
    VertexNumber = InitialValue;

    BTag = InitialValue;

    BdtBTag = InitialValue;

    BCutSigEff = InitialValue;

}
