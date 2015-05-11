# ifndef HEvent_hh
# define HEvent_hh

# include "HObject.hh"
# include "HParticle.hh"
# include "HLepton.hh"
# include "HJet.hh"
# include "TopHadronicTagger.hh"
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
    virtual void NewEvent(const ClonesArrays &) = 0;

    virtual Jets GetTops(HJetTag &) {
        Print(HError, "Get Tops", "No Tops");
        return Jets{};
    }

    virtual fastjet::PseudoJet GetHiggs() {
        Print(HError, "Get Higgs", "No Higgs");
        return fastjet::PseudoJet();
    }

    virtual Jets GetCandidates(HJetTag &) {
        Print(HError, "Get Candidates", "No Candidates");
         return Jets{};
    }

    HParticle *GetParticles() {
        return Particles;
    }

    HLepton *GetLeptons() {
        return Lepton;
    }

    HJet *GetJets() {
        return jets;
    }

    const HJet &Hadrons() const {
        return *jets;
    }

    const HLepton &Leptons() const {
        return *Lepton;
    }

    const HParticle &Partons() const {
        return *Particles;
    }

//     hanalysis::HTopTagger *GetTopTagger() {
//         return TopTagger;
//     }
//
//     hanalysis::HHiggsTagger *GetHiggsTagger() {
//         return HiggsTagger;
//     }
//
//     hanalysis::HDiscriminator *GetDiscriminator() {
//         return Discriminator;
//     }

    float GetMass() const {
        return Mass;
    }

    void SetMass(const float NewMass) {
        Mass = NewMass;
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
    HJet *jets;

    /**
     * @brief Tagged tops and their constituents
     *
     */
//     hanalysis::HTopTagger *TopTagger;

    /**
     * @brief Higgs
     *
     */
//     hanalysis::HHiggsTagger *HiggsTagger;

    /**
     * @brief SubJetInformation
     *
     */
//     hanalysis::HDiscriminator *Discriminator;

private:

    float Mass;

};

#endif

