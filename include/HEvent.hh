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

    virtual HJets GetTops(HJetTag &) {
        Print(HError, "Get Tops", "No Tops");
        HJets v;
        return v;
    }

    virtual fastjet::PseudoJet GetHiggs() {
        Print(HError, "Get Higgs", "No Higgs");
        fastjet::PseudoJet j;
        return j;
    }

    virtual HJets GetCandidates(HJetTag &) {
        Print(HError, "Get Candidates", "No Candidates");
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

    hanalysis::HTopTagger *GetTopTagger() {
        return TopTagger;
    }

    hanalysis::HHiggsTagger *GetHiggsTagger() {
        return HiggsTagger;
    }

    hanalysis::HDiscriminator *GetDiscriminator() {
        return Discriminator;
    }

    float GetMass() const{return Mass;}
    void SetMass(const float NewMass) {Mass=NewMass;}

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
    hanalysis::HTopTagger *TopTagger;

    /**
     * @brief Higgs
     *
     */
    hanalysis::HHiggsTagger *HiggsTagger;

    /**
     * @brief SubJetInformation
     *
     */
    hanalysis::HDiscriminator *Discriminator;

private:

  float Mass;

};

#endif

