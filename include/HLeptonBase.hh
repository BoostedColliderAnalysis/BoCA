# ifndef HLeptonBase_hh
# define HLeptonBase_hh

# include <algorithm>

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HConstants.hh"

using std::sort;
using std::vector;

class Jet;

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonBase : public HConstants
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
        
    void GetLeptonLorentzVectorVector();
    
    void GetAntiLeptonLorentzVectorVector();
    
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
    void TauTagCalculations(Jet *);
    
    /**
     * @brief lepton and  Missing-Energy
     *
     * @param ClonesArrayClass ...
     * @return void
     */
    void LeptonsAndMissingEt();
    
    void NewEvent(HClonesArrayBase *);

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> ElectronLorentzVectorVector;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiElectronLorentzVectorVector;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> MuonLorentzVectorVector;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiMuonLorentzVectorVector;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> TauLorentzVectorVector;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiTauLorentzVectorVector;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> LeptonLorentzVectorVector;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> AntiLeptonLorentzVectorVector;
    
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
