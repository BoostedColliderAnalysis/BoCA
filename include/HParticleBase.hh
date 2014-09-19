# ifndef HParticleBase_hh
# define HParticleBase_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HObject.hh"

using std::sort;
using std::vector;

/**
 * @brief stores all the information about the event topology
 *
 */
class HParticleBase : public HObject
{

public:

    /**
     * @brief constructor
     *
     */
    HParticleBase();

    /**
     * @brief destructor
     *
     */
    ~HParticleBase();

    void NewEvent(HClonesArrayBase *);

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    virtual bool GetParticles() = 0;

    virtual vector<TLorentzVector> LeptonVector();

    virtual vector<TLorentzVector> AntiLeptonVector();

    vector<TLorentzVector> TopVector;

    vector<TLorentzVector> AntiTopVector;

    vector<TLorentzVector> ElectronVector;

    vector<TLorentzVector> MuonVector;

    vector<TLorentzVector> AntiElectronVector;

    vector<TLorentzVector> AntiMuonVector;


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
    HClonesArrayBase *ClonesArrays;


private:

    virtual TString ClassName() {
        return ("HParticle");
    };

};

#endif
