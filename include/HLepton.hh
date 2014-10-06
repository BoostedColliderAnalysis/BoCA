# ifndef HLepton_hh
# define HLepton_hh

# include <algorithm>


# include "HClonesArray.hh"
# include "HObject.hh"

using std::sort;
using std::vector;

class Jet;

/**
 * @brief calculation regarding leptons
 *
 */
class HLepton : virtual public HObject
{

public:
    
    /**
     * @brief constructor
     *
     */
    HLepton();
        
    /**
     * @brief destructor
     *
     */
    ~HLepton();
    
    void NewEvent(HClonesArray *);
        
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
    
    HClonesArray *ClonesArray;

private:
    
    virtual string ClassName() const {
        
        return ("HLepton");
        
    };

};

#endif
