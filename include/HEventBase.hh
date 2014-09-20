# ifndef HEventBase_hh
# define HEventBase_hh

# include "HParticleBase.hh"
# include "HLeptonBase.hh"
# include "HJet.hh"
# include "HTopTagger.hh"
# include "HHiggsTagger.hh"
# include "HDiscriminator.hh"
# include "HObject.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventBase : public HObject
{

public:

    /**
    * @brief constructor
    *
    */
    HEventBase();

    /**
     * @brief destructor
     *
     */
    ~HEventBase();
    
    void NewEvent(HClonesArrayBase *);
    
    virtual void NewFile() = 0;
    
    virtual void CloseFile() = 0;
    
    virtual void NewEvent() = 0;

    virtual void GetParticles() = 0;

    virtual vector<TLorentzVector> GetLeptons() = 0;

    virtual void GetJets() = 0;

    virtual PseudoJet GetHiggs() = 0;
    
    virtual vector<PseudoJet> GetHiggsTopCandidates() = 0;

    virtual vector<PseudoJet> GetTops() = 0;

    /**
     * @brief Particles
     *
     */
    HParticleBase *Particle;

    /**
     * @brief Leptons
     *
     */
    HLeptonBase *Leptons;

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

    /**
     * @brief Clones Arrays
     *
     */
    HClonesArrayBase *ClonesArrays;

private:
    
    virtual TString ClassName() {
        return ("HEventBase");
    };
};

#endif

