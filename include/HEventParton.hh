# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEvent.hh"
# include "HParticleParton.hh"

/**
 * @brief Event topology for unweighted MadGraph events
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

    void NewEvent(const HClonesArray * const);

    void GetParticles();

private:

    bool HasParticles;

    inline string ClassName() const {

        return ("HEventParton");

    };
};

#endif

