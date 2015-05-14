# ifndef HEventParton_hh
# define HEventParton_hh

# include "Event.hh"

/**
 * @brief event topology for unweighted MadGraph events
 *
 */
class hanalysis::hparton::Event : public hanalysis::Event
{

public:

    /**
    * @brief constructor
    *
    */
    Event();

    /**
     * @brief destructor
     *
     */
    ~Event();

    void Newevent(const hanalysis::ClonesArrays &ClonesArrays);

private:

    inline std::string NameSpaceName() const {
        return "hparton";
    }

    inline std::string ClassName() const {
        return "Event";
    }
};

#endif

