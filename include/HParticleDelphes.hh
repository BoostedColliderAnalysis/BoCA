# ifndef HParticleDelphes_hh
# define HParticleDelphes_hh

# include "HParticle.hh"
# include "HFourVector.hh"
 
using std::abs;
 
/**
 * @brief stores all the information about the event topology
 *
 */
class HParticleDelphes : public HParticle, private HFourVectorDelphes
{

public:

    /**
     * @brief constructor
     *
     */
    HParticleDelphes();

    /**
     * @brief destructor
     *
     */
    ~HParticleDelphes();
    
    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles();
    
    vector<PseudoJet> TagJets(vector<PseudoJet>);
      
private:
    
    vector<PseudoJet> JetTagger(vector<PseudoJet>,vector<PseudoJet>, int);
    
    vector<PseudoJet> JetTagger(vector<PseudoJet>,vector<PseudoJet>);
    
    
    virtual TString ClassName() {
        return ("HParticleDelphes");
    };

};

#endif
