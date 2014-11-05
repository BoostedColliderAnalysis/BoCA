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

    void GetParticles();

    vector<TLorentzVector>GetLeptons();

    void GetJets();
    void GetStructuredJets();

    void GetTaggedJets(HJetTag *const JetTag);

    void GetEFlow();

    void GetTaggedEFlow(HJetTag *const JetTag);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(HJetTag *const JetTag);

    vector<PseudoJet> GetTops(HJetTag *const JetTag);

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(HJetTag *const JetTag);

protected:

    inline string ClassName() const {

        return "HDelphes: HEvent";

    };

private:

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

