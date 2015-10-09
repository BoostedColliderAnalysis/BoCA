#include "BranchesTopPartner.hh"
#include "Pair.hh"

namespace boca
{

namespace naturalness
{

SignatureSingleBranch::SignatureSingleBranch()
{
VetoBdt = InitialValue();
}


Observables SignatureSingleBranch::Variables()
{
    return Join(boca::TChannelBranch::Variables(),{PAIR(VetoBdt)});
}

SignatureSingleHadronicBranch::SignatureSingleHadronicBranch()
{
VetoBdt = InitialValue();
TopPt = InitialValue();
HiggsPt = InitialValue();
}

Observables SignatureSingleHadronicBranch::Variables()
{
  return Join(boca::TChannelBranch::Variables(),{PAIR(VetoBdt), PAIR(TopPt), PAIR(HiggsPt)});
}

Observables EventBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber), PAIR(BottomNumber), PAIR(JetNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
}

}

}
