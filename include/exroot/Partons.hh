/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Partons.hh"

namespace boca {

namespace exroot {

/**
 * @brief MadGraph particles
 *
 */
class Partons : public boca::Partons {

public:
  Jets Particles() const final;

  Jets GenParticles() const final;

private:

    Jets Particles(Status max_status) const;

};

}

}
