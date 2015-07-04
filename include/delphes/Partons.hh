#pragma once

#include "../Partons.hh"

namespace analysis
{

namespace delphes
{

/**
 * @brief delphes particles
 *
 */
class Partons  : public analysis::Partons
{

public:

    Jets Particles() const;

    Jets GenParticles() const;

private:

    Jets Particles(const Status max_status) const;

};

}

}
