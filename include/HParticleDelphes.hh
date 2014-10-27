# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"

using std::abs;

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

    /**
     * @brief Extracts particles from Clones Array
     *
     * @return bool
     */
    bool GetParticles();

private:

    inline string ClassName() const {

        return "HDelphes: HParticle";

    };

};

#endif
