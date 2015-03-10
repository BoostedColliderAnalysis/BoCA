# include "HBranchBTagger.hh"

ClassImp(hbtagger::HBTaggerBranch)

hbtagger::HBTaggerBranch::HBTaggerBranch()
{

    reset();

}

hbtagger::HBTaggerBranch::~HBTaggerBranch() {}

void hbtagger::HBTaggerBranch::reset()
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
