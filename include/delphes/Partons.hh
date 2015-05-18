# pragma once

# include "../Partons.hh"

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

    /**
     * @brief constructor
     *
     */
    Partons();

private:

    /**
     * @brief Extracts particles from Clones Array
     *
     * @return bool
     */
    bool GetParticles();

    inline std::string NameSpaceName() const {
        return "delphes";
    }

};

}

}
