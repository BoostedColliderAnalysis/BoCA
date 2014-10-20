# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticle.hh"

/**
 * @brief MadGraph particles
 *
 */
class HParticleParton : public HParticle
{

public:

    /**
     * @brief constructor
     *
     */
    HParticleParton();

    /**
     * @brief destructor
     *
     */
    ~HParticleParton();

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();

private:

    string ClassName() const {

        return ("HParticleParton");

    };

};

#endif
