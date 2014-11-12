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

    virtual HJets GetTops(HJetTag *const) {
        Print(0, "Get Tops", "No Tops");
        HJets v;
        return v;
    }

    virtual PseudoJet GetHiggs() {
        Print(0, "Get Higgs", "No Higgs");
        PseudoJet j;
        return j;
    }

    virtual HJets GetCandidates(HJetTag *const) {
        Print(0, "Get Candidates", "No Candidates");
        HJets v;
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

    hdelphes::HTopTagger *GetTopTagger() {
        return TopTagger;
    }

    hdelphes::HHiggsTagger *GetHiggsTagger() {
        return HiggsTagger;
    }

    hdelphes::HDiscriminator *GetDiscriminator() {
        return Discriminator;
    }

protected:

    virtual inline std::string ClassName() const {
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
    hdelphes::HTopTagger *TopTagger;

    /**
     * @brief Higgs
     *
     */
    hdelphes::HHiggsTagger *HiggsTagger;

    /**
     * @brief SubJetInformation
     *
     */
    hdelphes::HDiscriminator *Discriminator;

private:

};

#endif

