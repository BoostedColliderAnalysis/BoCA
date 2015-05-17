# pragma once

# include "HParticle.hh"

/**
 * @brief delphes particles
 *
 */
class analysis::hdelphes::HParticle  : public analysis::HParticle
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
