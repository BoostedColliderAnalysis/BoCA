# ifndef HEvent_hh
# define HEvent_hh

# include "HParticle.hh"
# include "HLepton.hh"
# include "HJet.hh"
# include "HTopTagger.hh"
# include "HHiggsTagger.hh"
# include "HDiscriminator.hh"
# include "HObject.hh"

/**
 * @brief stores all the information about the event topology
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
    
    void NewEvent(HClonesArray *);
    
    virtual void NewFile(){};
    
    virtual void CloseFile(){};
    
    virtual void NewEvent(){};

    virtual void GetParticles(){};

    virtual vector<TLorentzVector> GetLeptons(){vector<TLorentzVector> v; return v;};

    virtual void GetJets(){};

    virtual PseudoJet GetHiggs(){PseudoJet j; return j;};
    
    virtual vector<PseudoJet> GetHiggsTopCandidates(){vector<PseudoJet> v; return v;};

    virtual vector<PseudoJet> GetTops(){vector<PseudoJet> v; return v;};

    /**
     * @brief Particles
     *
     */
    HParticle *Particle;

    /**
     * @brief Leptons
     *
     */
    HLepton *Leptons;

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
    HClonesArray *ClonesArrays;

private:
    
    virtual TString ClassName() {
        return ("HEvent");
    };
};

#endif

