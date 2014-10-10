# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"

using std::abs;
 
/**
 * @brief handels information about truth level particles
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
    
    string ClassName() const {
        
        return ("HParticleDelphes");
        
    };

};

#endif
