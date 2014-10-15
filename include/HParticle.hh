# ifndef HParticle_hh
# define HParticle_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

using std::sort;
using std::vector;

/**
 * @brief stores all the information about the event topology
 *
 */
class HParticle : public HFourVector
{

public:

    /**
     * @brief constructor
     *
     */
    HParticle();

    /**
     * @brief destructor
     *
     */
    ~HParticle();

    void NewEvent(const HClonesArray * const);

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    virtual bool GetParticles() = 0;
    
    virtual vector<PseudoJet> TagJets( vector<PseudoJet>){vector<PseudoJet> v; return v;};

    virtual vector<TLorentzVector> LeptonVector();

    virtual vector<TLorentzVector> AntiLeptonVector();

    vector<TLorentzVector> TopVector;

    vector<TLorentzVector> AntiTopVector;

    vector<TLorentzVector> ElectronLorentzVectors;

    vector<TLorentzVector> MuonLorentzVectors;

    vector<TLorentzVector> AntiElectronLorentzVectors;

    vector<TLorentzVector> AntiMuonLorentzVectors;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    vector<PseudoJet> BottomJetVector;

    vector<PseudoJet> TopJetVector;


    /**
     * @brief Vector of generator level Higgs Pseudo Jets
     *
     */
    vector<PseudoJet> HiggsJetVector;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> CharmJetVector;
    

protected:


    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;
    
    vector<PseudoJet> ParticleJetVector;


private:

    virtual string ClassName() const {
        
        return ("HParticle");
        
    };

};

#endif
