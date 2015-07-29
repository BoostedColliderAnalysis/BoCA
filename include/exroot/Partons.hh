#pragma once

#include "../Partons.hh"

namespace analysis {

namespace exroot {

/**
 * @brief MadGraph particles
 *
 */
class Partons : public analysis::Partons {

public:
  Jets Particles() const final override;

  Jets GenParticles() const final override;

private:

    Jets Particles(const Status max_status) const;

};

}

}
