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

    void NewEvent(const hanalysis::HClonesArray * const ClonesArrays);

    vector<PseudoJet> GetTops(HJetTag *const JetTag);

    PseudoJet GetHiggs();

    vector<PseudoJet> GetCandidates(hanalysis::HJetTag *const JetTag);

protected:

  inline string NameSpaceName() const
  {
    return "HDelphes";
  }

    inline string ClassName() const {
        return "HEvent";
    };

private:

};

#endif

