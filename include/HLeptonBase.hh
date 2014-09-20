# ifndef HLeptonBase_hh
# define HLeptonBase_hh

# include <algorithm>

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HObject.hh"

using std::sort;
using std::vector;

class Jet;

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonBase : public HObject
{

public:
    
    /**
     * @brief constructor
     *
     */
    HLeptonBase();
    
    
    /**
     * @brief destructor
     *
     */
    ~HLeptonBase();
        
    vector<TLorentzVector> GetLeptonVector();
                
    vector<PseudoJet> GetLeptonJetVector();
    
    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    virtual void GetElectrons() = 0;
    
    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    virtual void GetMuons() = 0;
    
    /**
     * @brief Finds (Anti-)Tau with the largest Pt
     *
     * @param JetClone
     * @return void
     */
//     void TauTagCalculations(Jet *);
    
    /**
     * @brief lepton and  Missing-Energy
     *
     * @param ClonesArrayClass ...
     * @return void
     */
//     void LeptonsAndMissingEt();
    
    void NewEvent(HClonesArrayBase *);

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> ElectronVector;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiElectronVector;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> MuonVector;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiMuonVector;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> TauVector;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiTauVector;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> LeptonVector;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> AntiLeptonVector;
       

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    vector<PseudoJet> ElectronJetVector;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<PseudoJet> AntiElectronJetVector;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<PseudoJet> MuonJetVector;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<PseudoJet> AntiMuonJetVector;
    
    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> LeptonJetVector;
    
    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> AntiLeptonJetVector;
    
protected:
    
    HClonesArrayBase *ClonesArray;

private:
    
    virtual TString ClassName() {
        return ("HLeptonBase");
    };

};

#endif
