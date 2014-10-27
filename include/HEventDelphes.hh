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

    vector<TLorentzVector>GetLeptons();

    void GetJets();

    void GetEFlow();

    void GetTaggedEFlow(hanalysis::HJetTag *const JetTag);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(hanalysis::HJetTag *const JetTag);

    void GetParticles();

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(hanalysis::HJetTag *const JetTag);

    vector<PseudoJet> GetTops(const hanalysis::HJetTag *const JetTag);

    void GetTaggedJets(hanalysis::HJetTag *const JetTag);

private:

    inline string ClassName() const {

        return ("HDelphes: HEvent");

    };

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

