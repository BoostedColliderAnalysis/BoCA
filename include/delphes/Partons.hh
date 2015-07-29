#pragma once

#include "../Partons.hh"

namespace analysis {

namespace delphes {

/**
 * @brief delphes particles
 *
 */
class Partons  : public analysis::Partons {

public:
  Jets Particles() const final override;

  Jets GenParticles() const final override;

private:

    Jets Particles(const Status max_status) const;

};

}

}
