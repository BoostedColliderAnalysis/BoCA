# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"

using std::abs;

/**
 * @brief delphes particles
 *
 */
class HParticleDelphes : public HParticle
{

public:

    /**
     * @brief constructor
     *
     */
    HParticleDelphes();

    /**
     * @brief destructor
     *
     */
    ~HParticleDelphes();

    /**
     * @brief Extracts particles from Clones Array
     *
     * @return bool
     */
    bool GetParticles();

private:

    inline string ClassName() const {

        return ("HParticleDelphes");

    };

};

#endif
