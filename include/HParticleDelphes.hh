# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "classes/DelphesClasses.h"
# include "HParticle.hh"
 
/**
 * @brief stores all the information about the event topology
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
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();
      
private:
    
    
    virtual TString ClassName() {
        return ("HParticleDelphes");
    };

};

#endif
