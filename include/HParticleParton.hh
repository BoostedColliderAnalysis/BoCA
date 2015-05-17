# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticle.hh"

/**
 * @brief MadGraph particles
 *
 */
class analysis::hparton::HParticle : public analysis::HParticle
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
