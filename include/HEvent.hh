# ifndef HEvent_hh
# define HEvent_hh

# include "HObject.hh"
# include "HParticle.hh"
# include "HLepton.hh"
# include "HJet.hh"
# include "HTopTagger.hh"
# include "HHiggsTagger.hh"
# include "HDiscriminator.hh"
# include "HJetTag.hh"

/**
 * @brief Base class for the Event Topology
 *
 */
class hanalysis::HEvent : public HObject
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

    virtual void NewEvent(const HClonesArray * const ) = 0;

    virtual void GetParticles() {
        Print(0, "Get Particles", "No Particles");
    };

    virtual vector<TLorentzVector> GetLeptons() {
        Print(0, "Get Leptons", "No Leptons");
        vector<TLorentzVector> v;
        return v;
    };

    virtual void GetJets() {
        Print(0, "Get Jets", "No Jets");
    };

    virtual void GetTaggedJets(HJetTag *const) {
        Print(0, "Get Jets", "No Jets");
    };

    virtual void GetEFlow() {
        Print(0, "Get EFlow", "No EFlow");
    };

    virtual void GetTaggedEFlow(HJetTag *const) {
        Print(0, "Get EFlow", "No EFlow");
    };

    virtual void GetIsolatedEFlow() {
        Print(0, "Get EFlow", "No EFlow");
    };

    virtual void GetIsoaltedTaggedEFlow(HJetTag *const) {
        Print(0, "Get EFlow", "No EFlow");
    };

    virtual vector<PseudoJet> GetTops(HJetTag *const) {
        Print(0, "Get Tops", "No Tops");
        vector<PseudoJet> v;
        return v;
    }

    virtual PseudoJet GetHiggs() {
        Print(0, "Get Higgs", "No Higgs");
        PseudoJet j;
        return j;
    }

    virtual vector<PseudoJet> GetHiggsTopCandidates(HJetTag *const) {
        Print(0, "Get Candidates", "No Candidates");
        vector<PseudoJet> v;
        return v;
    }
    
    void SetJetTag(HJetTag *const JetTag){
        Jets->SetJetTag(JetTag);
    }

    HParticle *GetParticlesM() {
        return Particles;
    }

    HLepton *GetLeptonsM() {
        return Lepton;
    }

    HJet *GetJetsM() {
        return Jets;
    }

    HTopTagger *GetTopTaggerM() {
        return TopTagger;
    }

    HHiggsTagger *GetHiggsTaggerM() {
        return HiggsTagger;
    }

    HDiscriminator *GetDiscriminatorM() {
        return Discriminator;
    }

protected:

    virtual inline string ClassName() const {

        return "HEvent";

    };

    /**
     * @brief Particles
     *
     */
    HParticle *Particles;

    /**
     * @brief Leptons
     *
     */
    HLepton *Lepton;

    /**
     * @brief Jets
     *
     */
    HJet *Jets;

    /**
     * @brief Tagged tops and their constituents
     *
     */
    HTopTagger *TopTagger;

    /**
     * @brief Higgs
     *
     */
    HHiggsTagger *HiggsTagger;

    /**
     * @brief SubJetInformation
     *
     */
    HDiscriminator *Discriminator;

private:

};

#endif

