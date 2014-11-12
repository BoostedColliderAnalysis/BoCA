# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"

/**
 * @brief delphes particles
 *
 */
class hdelphes::HParticle  : public hanalysis::HParticle
{

public:

    /**
     * @brief constructor
     *
     */
    HParticle();

    /**
     * @brief destructor
     *
     */
    ~HParticle();

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

#endif
