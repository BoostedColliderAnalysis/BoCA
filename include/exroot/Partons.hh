#pragma once

#include "../Partons.hh"

namespace analysis
{

namespace exroot
{

/**
 * @brief MadGraph particles
 *
 */
class Partons : public analysis::Partons
{

public:

    Jets Particles() const;

    Jets GenParticles() const;

private:

    Jets Particles(const Status max_status) const;

};

}

}
