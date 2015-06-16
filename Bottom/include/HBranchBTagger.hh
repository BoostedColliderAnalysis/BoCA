# pragma once

# include "Branches.hh"

namespace analysis
{

namespace bottom {

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class HBTaggerBranch : public analysis::Branch
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

private:

    ClassDef(HBTaggerBranch, 1)

};

}

}
