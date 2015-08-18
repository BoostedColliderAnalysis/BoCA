#pragma once

#include "../Partons.hh"

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

    Jets Particles(const Status max_status) const;

};

}

}
