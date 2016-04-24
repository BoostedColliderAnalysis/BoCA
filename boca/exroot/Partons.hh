/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Partons.hh"

namespace boca {

namespace exroot {

/**
 * @brief MadGraph particles
 *
 */
class Partons : public boca::Partons {

public:

  Partons(boca::TreeReader const& tree_reader);

  std::vector<Particle> Particles() const override;

  std::vector<Particle> GenParticles() const override;

private:

  std::vector<Particle> Particles(Status max_status) const;

};

}

}
