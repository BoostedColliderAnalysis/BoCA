# ifndef HEventPgs_hh
# define HEventPgs_hh

# include "Event.hh"
# include "HLeptonPgs.hh"
# include "HJetPgs.hh"

/**
 * @brief event topology for PGS events
 *
 */
class hanalysis::hpgs::Event : public hanalysis::Event
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
      return "hpgs";
    }

    inline std::string ClassName() const {
        return "Event";
    };

};

#endif

