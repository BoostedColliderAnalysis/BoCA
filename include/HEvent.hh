# ifndef __HEVENT_HH__
# define __HEVENT_HH__

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
     * @brief SubJetInformation
     *
     */
    HDiscriminator *Discriminator;

    /**
     * @brief Tagged tops and their constituents
     *
     */
    HTopTagger *TaggedTopClass;

    vector<PseudoJet> TopJets;
    
    void NewFile();
    
    void CloseFile();

    void NewEvent(HClonesArrayBase *);

    void GetParticles();

    void GetJets();

    void GetLeptons();

    PseudoJet GetHiggs();

    /**
     * @brief Get Discriminator Higgs and Tops
     *
     * @param  Higgs
     * @param  Tops
     * @param  Candidates
     * @return Higgs
     */
    vector<PseudoJet> GetHiggsTopCandidates(bool, bool, bool);
    
    vector<PseudoJet> GetHiggsTopCandidates();

    vector<PseudoJet> GetTops();

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

    void CleanEvent();

private:

    /**
     * @brief Clones Arrays
     *
     */
    HClonesArrayBase *ClonesArrays;
    
    bool Particles;
    bool EFlow;
    
    virtual TString ClassName() {
        return ("HEvent");
    };

};

#endif

