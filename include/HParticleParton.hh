# ifndef HParticleParton_hh
# define HParticleParton_hh

# include "HParticleBase.hh"
# include "ExRootAnalysis/ExRootClasses.h"

/**
 * @brief stores all the information about the event topology
 *
 */
class HParticleParton : public HParticleBase
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
