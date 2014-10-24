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
class HEventDelphes : public HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEventDelphes();

    /**
     * @brief destructor
     *
     */
    ~HEventDelphes();

    void NewEvent(const HClonesArray * const);

    vector<TLorentzVector>GetLeptons();

    void GetJets();

    void GetEFlow();

    void GetTaggedEFlow(HJetTag *const JetTag);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(HJetTag *const JetTag);

    void GetParticles();

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(HJetTag *const JetTag);

    vector<PseudoJet> GetTops(const HJetTag *const JetTag);

    void GetTaggedJets(HJetTag *const JetTag);

private:

    inline string ClassName() const {

        return ("HEventDelphes");

    };

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

