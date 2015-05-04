# ifndef HLepton_hh
# define HLepton_hh

# include <algorithm>

# include "ClonesArrays.hh"
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

    void NewEvent(const hanalysis::ClonesArrays &NewClonesArrays);

    HVectors GetLeptonVectors();


    HJets GetLeptonJets();

    HJets GetTaggedJets(HJetTag &NewJetTag) {
        JetTag = &NewJetTag;
        return GetLeptonJets(hanalysis::HFourVector::Tagging);
    };

protected:

    HJets GetLeptonJets(hanalysis::HFourVector::HJetDetails JetDetails);

  /**
   * @brief Find the hardest of the light leptons
   *
   */
  virtual bool GetElectrons(HJetDetails JetDetails) {
    Print(HError,"should be subclassed",JetDetails);
    return 0;
  }

  /**
   * @brief Find the hardest of the light leptons
   *
   */
  virtual bool GetMuons(HJetDetails JetDetails) {
    Print(HError,"should be subclassed",JetDetails);
    return 0;
  }

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

//     const HClonesArray *ClonesArrays;

private:

    virtual inline std::string ClassName() const {

        return ("HLepton");

    };

};

#endif
