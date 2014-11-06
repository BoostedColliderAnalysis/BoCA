# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"

// using std::abs;

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

    inline string NameSpaceName() const {
        return "HDelphes";
    }

    inline string ClassName() const {
        return "HParticle";
    }

};

#endif
