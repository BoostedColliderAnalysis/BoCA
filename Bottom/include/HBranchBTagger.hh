# pragma once

# include "TObject.h"
# include "Rtypes.h"
# include "TGenericClassInfo.h"

namespace bottom {

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class HBTaggerBranch : public TObject
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

}
