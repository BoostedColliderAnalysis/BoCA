# ifndef HLepton_hh
# define HLepton_hh

# include <algorithm>

# include "HClonesArray.hh"
# include "HFourVector.hh"

using std::sort;
using std::vector;

// class Jet;

/**
 * @brief calculation regarding leptons
 *
 */
class Analysis::HLepton : public HFourVector
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

    void NewEvent(const HClonesArray * const);

    vector<TLorentzVector> GetLeptonLorentzVectors();

    vector<PseudoJet> GetLeptonJets();

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
    vector<TLorentzVector> ElectronLorentzVectors;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiElectronLorentzVectors;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> MuonLorentzVectors;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiMuonLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiTauLorentzVectors;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> LeptonLorentzVectors;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> AntiLeptonLorentzVectors;


    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    vector<PseudoJet> ElectronJets;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<PseudoJet> AntiElectronJets;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<PseudoJet> MuonJets;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<PseudoJet> AntiMuonJets;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> LeptonJets;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> AntiLeptonJets;

protected:

    const HClonesArray *ClonesArray;

private:

    virtual inline string ClassName() const {

        return ("HLepton");

    };

};

#endif
