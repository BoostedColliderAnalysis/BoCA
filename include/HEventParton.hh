# ifndef HEventParton_hh
# define HEventParton_hh

# include "HEvent.hh"

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

    void NewEvent(const hanalysis::ClonesArrays &ClonesArrays);

private:

    inline std::string NameSpaceName() const {
        return "hparton";
    }

    inline std::string ClassName() const {
        return "HEvent";
    }
};

#endif

