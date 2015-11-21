/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Partons.hh"

class GenParticle;
namespace delphes
{
typedef ::GenParticle GenParticle;
}

namespace boca
{

namespace delphes
{

/**
 * @brief delphes particles
 *
 */
class Partons  : public boca::Partons
{

public:

    std::vector<Particle> Particles() const final;

    std::vector<Particle> GenParticles() const final;

private:

    std::vector<Particle> Particles(Status max_status) const;

};

}

}
