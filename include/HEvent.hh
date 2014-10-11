# ifndef HEvent_hh
# define HEvent_hh

# include "HParticle.hh"
# include "HLepton.hh"
# include "HJet.hh"
# include "HTopTagger.hh"
# include "HHiggsTagger.hh"
# include "HDiscriminator.hh"
# include "HObject.hh"
# include "HJetTag.hh"

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
        
    virtual void NewFile(){};
    
    virtual void CloseFile(){};
    
    virtual void NewEvent(const HClonesArray * const) = 0;
    
    virtual void GetParticles(){};

    virtual vector<TLorentzVector> GetLeptons(){vector<TLorentzVector> v; return v;};

    virtual void GetJets(){};
    
    virtual void GetEFlow(){};
    
    virtual void GetTaggedEFlow(const HJetTag *const){};

    virtual PseudoJet GetHiggs(){PseudoJet j; return j;};
    
    virtual vector<PseudoJet> GetHiggsTopCandidates(const HJetTag *const){vector<PseudoJet> v; return v;};

    virtual vector<PseudoJet> GetTops(){vector<PseudoJet> v; return v;};
    
    virtual void GetTaggedJets(){};

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

    /**
     * @brief Clones Arrays
     *
     */
//     HClonesArray *ClonesArrays;

private:
    
    virtual string ClassName() const {
        
        return ("HEvent");
        
    };
};

#endif

