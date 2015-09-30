#include "BranchesTopPartner.hh"
#include "Pair.hh"

namespace boca
{

namespace naturalness
{

Observables SignatureSingleBranch::Variables()
{
    return Join(boca::TChannelBranch::Variables(),{PAIR(VetoBdt)});
}

Observables EventBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber), PAIR(BottomNumber), PAIR(JetNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
}

}

}
