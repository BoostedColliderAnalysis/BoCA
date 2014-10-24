# ifndef HParticle_hh
# define HParticle_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

using std::sort;
using std::vector;

/**
 * @brief particles for HAnalysis
 *
 */
class Analysis::HParticle : public HFourVector
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

    virtual vector<TLorentzVector> GetLeptonLorentzVectors();

    virtual vector<TLorentzVector> GetAntiLeptonLorentzVectors();

    virtual vector<PseudoJet> GetLeptonJets();

    virtual vector<PseudoJet> GetAntiLeptonJets();

    vector<TLorentzVector> TopVector;

    vector<TLorentzVector> AntiTopVector;

    vector<TLorentzVector> ElectronLorentzVectors;

    vector<TLorentzVector> MuonLorentzVectors;

    vector<TLorentzVector> AntiElectronLorentzVectors;

    vector<TLorentzVector> AntiMuonLorentzVectors;

    vector<PseudoJet> ElectronJets;

    vector<PseudoJet> MuonJets;

    vector<PseudoJet> AntiElectronJets;

    vector<PseudoJet> AntiMuonJets;


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

    virtual inline string ClassName() const {

        return ("HParticle");

    };

};

#endif
