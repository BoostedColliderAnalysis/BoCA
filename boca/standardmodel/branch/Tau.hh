/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Particle.hh"

namespace boca
{

namespace standardmodel
{

namespace branch {

/**
 *
 * @brief Tau tagger root tree structure
 *
 */
class Tau : public boca::branch::Particle
{
public:
    Tau();
    float EmRadius;
    float TrackRadius;
    float MomentumFraction;
    float CoreEnergyFraction;
    float EmFraction;
    float ClusterMass;
    float TrackMass;
    float FlightPath;
    float TrtHtFraction;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Particle::Fill(multiplet);
        EmRadius = multiplet.EmRadius() / rad;
        TrackRadius = multiplet.TrackRadius() / rad;
        MomentumFraction = multiplet.Info().LeadingTrackMomentumFraction();
        CoreEnergyFraction = multiplet.CoreEnergyFraction();
        EmFraction = multiplet.Info().ElectroMagneticFraction();
        ClusterMass = multiplet.Info().ClusterMass() / GeV;
        TrackMass = multiplet.Info().TrackMass() / GeV;
        FlightPath = multiplet.FlightPath();
        TrtHtFraction = multiplet.TrtHtFraction();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(Tau, 1)
};

}

}

}
