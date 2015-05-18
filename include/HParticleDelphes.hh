# pragma once

# include "Partons.hh"

/**
 * @brief delphes particles
 *
 */
class analysis::delphes::HParticle  : public analysis::Partons
{

public:

    /**
     * @brief constructor
     *
     */
    HParticle();

private:

    /**
     * @brief Extracts particles from Clones Array
     *
     * @return bool
     */
    bool GetParticles();

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HParticle";
    }

};
