# pragma once

# include "../Partons.hh"

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

    Partons();

    Jets Particles();

    Jets GenParticles();

private:

    Jets Particles(const Status max_status);

    inline std::string NameSpaceName() const {
        return "exroot";
    }

};

}

}
