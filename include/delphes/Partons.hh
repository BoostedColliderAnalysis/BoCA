/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Partons.hh"

class GenParticle;
namespace delphes{
  typedef ::GenParticle GenParticle;
}

namespace boca {

namespace delphes {

/**
 * @brief delphes particles
 *
 */
class Partons  : public boca::Partons {

public:
  Jets Particles() const final;

  Jets GenParticles() const final;

private:

  Jets Particles(Status max_status) const;

//   int MotherId(::delphes::GenParticle& particle);

};

}

}
