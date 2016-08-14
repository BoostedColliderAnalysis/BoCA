#include "include/branch/JetPair.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

JetPair::JetPair()
{
  //     DeltaM = InitialValue();
  Jet1Mass = InitialValue();
  Jet1Pt = InitialValue();
  Jet1Rap = InitialValue();
  Jet1Phi = InitialValue();
  //     Jet1Bdt = InitialValue();
  //     Jet1BTag = InitialValue();
  Jet2Mass = InitialValue();
  Jet2Pt = InitialValue();
  Jet2Rap = InitialValue();
  Jet2Phi = InitialValue();
  //     Jet2Bdt = InitialValue();
  //     Jet2BTag = InitialValue();
  //     BdtRatio11 = InitialValue();
  //     BdtRatio12 = InitialValue();
  //     BdtRatio13 = InitialValue();
  //     BdtRatio14 = InitialValue();
  //     BdtRatio21 = InitialValue();
  //     BdtRatio22 = InitialValue();
  //     BdtRatio23 = InitialValue();
  //     BdtRatio24 = InitialValue();
}


Observables JetPair::Variables()
{
  return TwoBody::Variables() + OBSERVABLE(Jet1Mass) + OBSERVABLE(Jet1Pt) + OBSERVABLE(Jet1Rap) + OBSERVABLE(Jet1Phi) + OBSERVABLE(Jet2Mass) + OBSERVABLE(Jet2Pt) + OBSERVABLE(Jet2Rap) + OBSERVABLE(Jet2Phi);
}

}

}

