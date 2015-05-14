# pragma once

# include "HParticle.hh"

/**
 * @brief delphes particles
 *
 */
class hanalysis::hdelphes::HParticle  : public hanalysis::HParticle
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
