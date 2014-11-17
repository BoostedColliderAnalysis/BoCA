# ifndef HBranchHiggsCpv_hh
# define HBranchHiggsCpv_hh

# include "TObject.h"
# include "Rtypes.h"


namespace hbtagger
{

class HDiscriminator;
class HJetTag;
class JetHJetTag;
class HAnalysis;
class HBranchDiscriminator;
class HJetDiscriminator;
class HMva;
class HBTaggerBranch;
class HLeptonBranch;

}

/**
 *
 * @brief Class for saving reconstructed candidates to root
 *
 */
class hbtagger::HBTaggerBranch : public TObject
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


# endif
