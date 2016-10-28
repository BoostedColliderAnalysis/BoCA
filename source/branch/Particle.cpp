/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Particle.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

Particle::Particle()
{
    mass = InitialValue();
    pt = InitialValue();
    rap = InitialValue();
    phi = InitialValue();
    charge = static_cast<int>(InitialValue());
}

Observables Particle::Variables()
{
    return Bdt::Variables() + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(pt, latex::String("p_{T}") + "[GeV]") + OBSERVABLE(rap, "\\eta") + OBSERVABLE(phi, "\\phi");
}

Observables Particle::Spectators()
{
    return Bdt::Spectators() + OBSERVABLE(charge, "e");
}

}

}
