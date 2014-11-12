# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEvent.hh"
# include "HParticleParton.hh"

/**
 * @brief Event topology for unweighted MadGraph events
 *
 */
class hparton::HEvent : public hanalysis::HEvent
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

    inline std::string NameSpaceName() const {
        return "HParton";
    }

    inline std::string ClassName() const {
        return "HEvent";
    }
};

#endif

