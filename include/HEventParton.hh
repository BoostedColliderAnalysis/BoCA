# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEventBase.hh"
# include "HParticleParton.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventParton : public HEventBase
{

public:

    /**
    * @brief constructor
    *
    */
    HEventDelphes();

    /**
     * @brief destructor
     *
     */
    ~HEventDelphes();
    
    void NewEvent();
    
    void GetParticles();

private:
    
    bool Particles;
    
    virtual TString ClassName() {
        return ("HEventParton");
    };
};

#endif

