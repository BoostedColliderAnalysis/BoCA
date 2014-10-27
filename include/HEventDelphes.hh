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

    void NewEvent(const HClonesArray *const ClonesArrays);

    vector<TLorentzVector>GetLeptons();

    void GetJets();

    void GetEFlow();

    void GetTaggedEFlow(HJetTag *const JetTag);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(HJetTag *const JetTag);

    void GetParticles();

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(HJetTag *const JetTag);

    vector<PseudoJet> GetTops(HJetTag *const JetTag);

    void GetTaggedJets(HJetTag *const JetTag);

private:

    inline string ClassName() const {

        return ("HDelphes: HEvent");

    };

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

