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

private:

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();

    inline std::string NameSpaceName() const {
        return "HParton";
    }

    inline std::string ClassName() const {
        return "HParticle";
    }

};

#endif
