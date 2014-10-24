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
class HEvent : public HObject
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

//     virtual void NewFile() {};

//     virtual void CloseFile() {};

    virtual void NewEvent(const HClonesArray * const) = 0;

    virtual void GetParticles() {};

    virtual vector<TLorentzVector> GetLeptons() {
        vector<TLorentzVector> v;
        return v;
    };

    virtual void GetJets() {};

    virtual void GetEFlow() {};

    virtual void GetTaggedEFlow(const HJetTag *const) {};

    virtual PseudoJet GetHiggs() {
        PseudoJet j;
        return j;
    };

    virtual vector<PseudoJet> GetHiggsTopCandidates(HJetTag *const) {
        vector<PseudoJet> v;
        return v;
    };

    virtual vector<PseudoJet> GetTops(HJetTag * const) {
        vector<PseudoJet> v;
        return v;
    };

    virtual void GetTaggedJets(HJetTag *const) {};

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
     * @brief Higgs
     *
     */
    HHiggsTagger *HiggsTagger;

    /**
     * @brief Tagged tops and their constituents
     *
     */
    HTopTagger *TopTagger;

    /**
     * @brief SubJetInformation
     *
     */
    HDiscriminator *Discriminator;

protected:

private:

    virtual inline string ClassName() const {

        return ("HEvent");

    };
};

#endif

