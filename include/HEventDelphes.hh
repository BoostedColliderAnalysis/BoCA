# ifndef HEventDelphes_hh
# define HEventDelphes_hh

# include "HEvent.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventDelphes : public HEvent
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

    vector<TLorentzVector>GetLeptons();

    void GetJets();
    
    void GetParticles();

    PseudoJet GetHiggs();
    
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

