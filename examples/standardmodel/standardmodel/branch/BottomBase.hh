/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TObject.h"
#include "boca/physics/Prefixes.hh"
#include "boca/Observables.hh"

namespace standardmodel
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief %Bottom tagger base tree branch
 * @details this construct is necessary because root can not handel virtual inheritance needed for the resulution of the dreaded diamond
 *
 */
class BottomBase
{

public:

    BottomBase();

    float vertex_mass;
    float max_displacement;
    float mean_displacement;
    float sum_displacement;
    float multiplicity;
    float radius;
    float spread;
    float vertex_radius;
    float vertex_spread;
    float energy_fraction;
    float energy_ratio;
    float momentum_ratio;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Fill2(multiplet.ConstituentJet());
    }

    template<typename Singlet>
    void Fill2(Singlet const& singlet) {
        vertex_mass = singlet.Info().VertexMass() / GeV;
        max_displacement = singlet.MaxDisplacement();
        mean_displacement = singlet.MeanDisplacement();
        sum_displacement = singlet.SumDisplacement();
        multiplicity = singlet.Info().VertexNumber();
        radius = singlet.Radius() / rad;
        spread = singlet.Spread();
        vertex_radius = singlet.VertexRadius() / rad;
        vertex_spread = singlet.VertexSpread();
        energy_fraction = singlet.EnergyFraction();
        energy_ratio = singlet.EnergyRatio();
        momentum_ratio = singlet.MomentumRatio();
    }

    virtual boca::Observables Variables();

    virtual boca::Observables Spectators();

private:

    float InValue();

};

}

}
