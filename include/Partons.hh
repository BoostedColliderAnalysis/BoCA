/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Particle.hh"
#include "FourVector.hh"

namespace boca {

/**
 * @brief particles for HAnalysis
 *
 */
class Partons : public FourVector {

public:

    virtual ~Partons() {};

    void NewEvent(const TreeReader& tree_reader);

    virtual std::vector<Particle> Particles() const = 0;

    virtual std::vector<Particle> GenParticles() const = 0;

};

}
