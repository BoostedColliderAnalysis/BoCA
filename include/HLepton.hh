# ifndef HLepton_hh
# define HLepton_hh

# include <algorithm>

# include "HClonesArray.hh"
# include "HFourVector.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HLepton : public HFourVector
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

    void NewEvent(const HClonesArray *const);

    HVectors GetLeptonLorentzVectors();

    HJets GetLeptonJets();

protected:

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  virtual bool GetElectrons() = 0;

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  virtual bool GetMuons() = 0;

  bool GotElectrons;
  bool GotMuons;

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    HVectors ElectronLorentzVectors;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    HVectors AntiElectronLorentzVectors;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    HVectors MuonLorentzVectors;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    HVectors AntiMuonLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    HVectors TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    HVectors AntiTauLorentzVectors;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    HVectors LeptonLorentzVectors;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    HVectors AntiLeptonLorentzVectors;


    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    HJets ElectronJets;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    HJets AntiElectronJets;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    HJets MuonJets;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    HJets AntiMuonJets;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    HJets LeptonJets;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    HJets AntiLeptonJets;

    const HClonesArray *ClonesArray;

private:

    virtual inline std::string ClassName() const {

        return ("HLepton");

    };

};

#endif
