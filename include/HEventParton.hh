# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEvent.hh"
# include "HParticleParton.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventParton : public HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEventParton();

    /**
     * @brief destructor
     *
     */
    ~HEventParton();
    
    void NewEvent(HClonesArray *);
    
    void GetParticles();

private:
    
    bool HasParticles;
    
    TString ClassName() const {
        
        return ("HEventParton");
        
    };
};

#endif

