/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Particle.hh"
#include "FourVector.hh"

namespace boca
{

enum class Status
{
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};

/**
 * @brief particles for HAnalysis
 *
 */
class Partons : public FourVector
{

public:

    Partons(boca::TreeReader const& tree_reader);

    virtual ~Partons();

    virtual std::vector<Particle> Particles() const = 0;

    virtual std::vector<Particle> GenParticles() const = 0;

};

}
