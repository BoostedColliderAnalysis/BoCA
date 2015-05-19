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

    /**
     * @brief constructor
     *
     */
    Partons();

private:

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();

    inline std::string NameSpaceName() const {
        return "parton";
    }

};

}

}
