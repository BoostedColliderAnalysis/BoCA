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
class Analysis::HDelphes::HEvent  : public Analysis::HEvent
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

    void NewEvent(const Analysis::HClonesArray *const ClonesArrays);

    vector<TLorentzVector>GetLeptons();

    void GetJets();

    void GetEFlow();

    void GetTaggedEFlow(Analysis::HJetTag *const JetTag);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(Analysis::HJetTag *const JetTag);

    void GetParticles();

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(Analysis::HJetTag *const JetTag);

    vector<PseudoJet> GetTops(const Analysis::HJetTag *const JetTag);

    void GetTaggedJets(Analysis::HJetTag *const JetTag);

private:

    inline string ClassName() const {

        return ("HDelphes: HEvent");

    };

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

