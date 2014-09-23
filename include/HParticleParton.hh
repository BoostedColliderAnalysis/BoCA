# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticle.hh"
# include "HFourVector.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HParticleParton : public HParticle, public HFourVectorExRoot
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
    
    virtual TString ClassName() {
        return ("HParticleParton");
    };

};

#endif
