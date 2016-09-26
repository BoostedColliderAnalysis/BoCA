/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/branch/TopLeptonic.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace standardmodel
{

namespace branch {

TopLeptonic::TopLeptonic()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonic::Variables()
{
    return BottomBase::Variables() + Particle::Variables() +
  OBSERVABLE(ht, latex::String("H_{T}") + " [GeV]") +
  OBSERVABLE(delta_pt, latex::String("\\delta_ P_{T}") + " [GeV]") +
  OBSERVABLE(delta_m, latex::String("\\delta_ m") + " [GeV]") +
  OBSERVABLE(delta_rap, latex::String("\\delta_ \\eta")) +
  OBSERVABLE(delta_phi, latex::String("\\delta_ \\phi")) +
  OBSERVABLE(delta_r, latex::String("\\delta_ R")) +
  OBSERVABLE(rho, latex::String("\\rho")) +
  OBSERVABLE(bdt_1, "BDT_{1}") +
  OBSERVABLE(bdt_2, "BDT_{2}") +
  OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
  OBSERVABLE(pull_2, latex::String("#theta_{2}"))
//     + OBSERVABLE(Dipolarity, latex::String("D"))
    ;

//   Particle::Variables() +
//   OBSERVABLE(ht) +
//   OBSERVABLE(delta_pt) +
//   OBSERVABLE(delta_m) +
//   OBSERVABLE(delta_rap) +
//   OBSERVABLE(delta_phi) +
//   OBSERVABLE(delta_r) +
//   OBSERVABLE(rho) +
//   OBSERVABLE(bdt_2) +
//   OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
//   OBSERVABLE(pull_2, latex::String("#theta")) +
//   OBSERVABLE(bdt_1);
}

Observables TopLeptonic::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}
