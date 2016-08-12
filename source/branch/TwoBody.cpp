/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/TwoBody.hh"
#include "boca/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

TwoBody::TwoBody()
{
  ht = InitialValue();
    delta_pt = InitialValue();
    delta_m = InitialValue();
    delta_rap = InitialValue();
    delta_phi = InitialValue();
    delta_r = InitialValue();
    rho = InitialValue();
    bdt_1 = InitialValue();
    bdt_2 = InitialValue();
    pull_1 = InitialValue();
    pull_2 = InitialValue();
//     Dipolarity = InitialValue();
}

Observables TwoBody::Variables()
{
  return Particle::Variables() +
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
  OBSERVABLE(pull_2, latex::String("#theta_{2}"));
}

Observables TwoBody::Spectators()
{
  return Particle::Spectators() + OBSERVABLE(dipolarity, latex::String("D"));
}

}

}
