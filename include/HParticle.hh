# ifndef HParticle_hh
# define HParticle_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

// using std::sort;
// using std::vector;

/**
 * @brief particles for HAnalysis
 *
 */
class hanalysis::HParticle : public HFourVector
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

    void NewEvent(const HClonesArray *const);

    vector<TLorentzVector> GetLeptonLorentzVectors();

    vector<TLorentzVector> GetAntiLeptonLorentzVectors();

    vector<PseudoJet> GetLeptonJets();

    vector<PseudoJet> GetAntiLeptonJets();

    vector<PseudoJet> GetBottomJets()  {
        if(!GotParticles) GotParticles = GetParticles();
        return BottomJetVector;
    }

    vector<PseudoJet> GetCharmJets() {
      if(!GotParticles) GotParticles = GetParticles();
        return CharmJetVector;
    }

    vector<PseudoJet> GetTopJets() {
      if(!GotParticles) GotParticles = GetParticles();
        return TopJetVector;
    }

protected:

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    virtual bool GetParticles() = 0;

    bool GotParticles;

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


    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;

    vector<PseudoJet> ParticleJetVector;

    virtual inline string ClassName() const {
        return ("HParticle");
    };

private:

};

#endif
