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

    virtual vector<PseudoJet> GetCandidates(HJetTag *const) {
        Print(0, "Get Candidates", "No Candidates");
        vector<PseudoJet> v;
        return v;
    }

    HParticle *GetParticles() {
        return Particles;
    }

    HLepton *GetLeptons() {
        return Lepton;
    }

    HJet *GetJets() {
        return Jets;
    }

    HTopTagger *GetTopTagger() {
        return TopTagger;
    }

    HHiggsTagger *GetHiggsTagger() {
        return HiggsTagger;
    }

    HDiscriminator *GetDiscriminator() {
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

