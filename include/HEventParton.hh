# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEvent.hh"
# include "HParticleParton.hh"

/**
 * @brief Event topology for unweighted MadGraph events
 *
 */
class hanalysis::hparton::HEvent : public hanalysis::HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEvent();

    /**
     * @brief destructor
     *
     */
    ~HEvent();

    void NewEvent(const hanalysis::hparton::HClonesArray *const ClonesArrays);

    void GetParticles();

private:

    bool HasParticles;

    inline string ClassName() const {

        return ("HParton: HEvent");

    };
};

#endif

