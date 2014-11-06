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

    void NewEvent(const hanalysis::HClonesArray *const ClonesArrays);

private:

    inline string NameSpaceName() const {
        return "HParton";
    }

    inline string ClassName() const {
        return "HEvent";
    }
};

#endif

