/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/Tau.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace standardmodel
{

namespace branch {

Tau::Tau()
{
    EmRadius = InitialValue();
    TrackRadius = InitialValue();
    MomentumFraction = InitialValue();
    CoreEnergyFraction = InitialValue();
    EmFraction = InitialValue();
    ClusterMass = InitialValue();
    TrackMass = InitialValue();
    FlightPath = InitialValue();
    TrtHtFraction = InitialValue();
}

Observables Tau::Variables()
{
    return Particle::Variables() + OBSERVABLE(EmRadius) + OBSERVABLE(TrackRadius) + OBSERVABLE(MomentumFraction) + OBSERVABLE(CoreEnergyFraction) + OBSERVABLE(EmFraction) + OBSERVABLE(ClusterMass) + OBSERVABLE(TrackMass) + OBSERVABLE(FlightPath) + OBSERVABLE(TrtHtFraction);
}

Observables Tau::Spectators()
{
    return Particle::Spectators();
}

}

}

}
