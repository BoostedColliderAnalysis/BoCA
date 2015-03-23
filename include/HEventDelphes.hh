# ifndef HEventDelphes_hh
# define HEventDelphes_hh

# include "HEvent.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"
# include "HJetDelphes.hh"

/**
 * @brief event topology for Delphes events
 *
 */
class hanalysis::hdelphes::HEvent  : public hanalysis::HEvent
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

    HJets GetTops(hanalysis::HJetTag &JetTag);

    fastjet::PseudoJet GetHiggs();

    HJets GetCandidates(hanalysis::HJetTag &JetTag);


protected:

    inline std::string NameSpaceName() const {
        return "hdelphes";
    }

    inline std::string ClassName() const {
        return "HEvent";
    };

private:

};

#endif

