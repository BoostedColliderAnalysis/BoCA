# ifndef HEventDelphes_hh
# define HEventDelphes_hh

# include "HEventBase.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventDelphes : public HEventBase
{

public:

    /**
    * @brief constructor
    *
    */
    HEventDelphes();

    /**
     * @brief destructor
     *
     */
    ~HEventDelphes();
    
    void NewFile();
    
    void CloseFile();

    void NewEvent();

    void GetLeptons();

    void GetJets();
    
    void GetParticles();

    PseudoJet GetHiggs();

//     /**
//      * @brief Get Discriminator Higgs and Tops
//      *
//      * @param  Higgs
//      * @param  Tops
//      * @param  Candidates
//      * @return Higgs
//      */
//     vector<PseudoJet> GetHiggsTopCandidates(bool, bool, bool);
    
    vector<PseudoJet> GetHiggsTopCandidates();

    vector<PseudoJet> GetTops();

private:
    
    virtual TString ClassName() {
        return ("HEventDelphes");
    };
    
    bool EFlow;
    
    bool Particles;

};

#endif

