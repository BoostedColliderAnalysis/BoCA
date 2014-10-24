# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticle.hh"

/**
 * @brief MadGraph particles
 *
 */
class HParton::HParticle : public Analysis::HParticle
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
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();

private:

    inline string ClassName() const {

        return "HParton: HParticle";

    };

};

#endif
