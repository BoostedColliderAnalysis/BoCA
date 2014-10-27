# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticle.hh"

/**
 * @brief MadGraph particles
 *
 */
class hanalysis::hparton::HParticle : public hanalysis::HParticle
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
