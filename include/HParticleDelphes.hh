# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"
# include "classes/DelphesClasses.h"
 
using std::abs;
 
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
    
    string ClassName() const {
        
        return ("HParticleDelphes");
        
    };

};

#endif
