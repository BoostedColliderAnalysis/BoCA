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
  Jets Particles() const final;

  Jets GenParticles() const final;

private:

    Jets Particles(Status max_status) const;

};

}

}
