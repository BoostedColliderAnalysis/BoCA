# ifndef HEventDelphes_hh
# define HEventDelphes_hh

# include "Event.hh"

/**
 * @brief event topology for Delphes events
 *
 */
class hanalysis::hdelphes::Event  : public hanalysis::Event
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

//     Jets GetTops(hanalysis::HJetTag &JetTag);

//     fastjet::PseudoJet GetHiggs();

//     Jets GetCandidates(hanalysis::HJetTag &JetTag);


protected:

    inline std::string NameSpaceName() const {
        return "hdelphes";
    }

    inline std::string ClassName() const {
        return "Event";
    };

private:

};

#endif

