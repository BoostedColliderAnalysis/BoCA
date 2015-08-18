#include "BranchesTopPartner.hh"
#include "Pair.hh"

namespace boca
{

namespace naturalness
{

Observables EventBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber), PAIR(BottomNumber), PAIR(JetNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
}

Observables EventBranch::Spectators() const
{
  return Join(MultiBranch::Spectators(), {});
}

}

}
