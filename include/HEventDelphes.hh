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

    void GetTaggedEFlow(const HJetTag * const);

    void GetIsolatedEFlow();

    void GetIsoaltedTaggedEFlow(const HJetTag * const);

    void GetParticles();

    PseudoJet GetHiggs();

    vector<PseudoJet> GetHiggsTopCandidates(const HJetTag * const);

    vector<PseudoJet> GetTops();

    void GetTaggedJets(const HJetTag * const);

private:

    string ClassName() const {

        return ("HEventDelphes");

    };

    bool HasEFlow;

    bool HasParticles;

    bool HasJets;

};

#endif

