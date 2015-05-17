# ifndef HLepton_hh
# define HLepton_hh

# include <algorithm>

# include "ClonesArrays.hh"
# include "FourVector.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class analysis::HLepton : public FourVector
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
    virtual ~HLepton();

    void NewEvent(const analysis::ClonesArrays &NewClonesArrays);

    Vectors GetLeptonVectors();


    Jets GetLeptonJets();

    Jets GetTaggedJets(HJetTag &NewJetTag) {
        jet_tag_ = &NewJetTag;
        return GetLeptonJets(analysis::FourVector::Tagging);
    };

protected:

    Jets GetLeptonJets(analysis::FourVector::HJetDetails JetDetails);

  /**
   * @brief Find the hardest of the light leptons
   *
   */
  virtual bool GetElectrons(HJetDetails JetDetails) {
    Print(kError,"should be subclassed",JetDetails);
    return 0;
  }

  /**
   * @brief Find the hardest of the light leptons
   *
   */
  virtual bool GetMuons(HJetDetails JetDetails) {
    Print(kError,"should be subclassed",JetDetails);
    return 0;
  }

  bool GotElectrons;

  bool GotMuons;

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    Vectors ElectronLorentzVectors;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    Vectors AntiElectronLorentzVectors;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    Vectors MuonLorentzVectors;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    Vectors AntiMuonLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    Vectors TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    Vectors AntiTauLorentzVectors;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    Vectors LeptonLorentzVectors;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    Vectors AntiLeptonLorentzVectors;


    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    Jets ElectronJets;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    Jets AntiElectronJets;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    Jets MuonJets;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    Jets AntiMuonJets;

    /**
     * @brief Lepton Lorentz Vector
     *
     */
    Jets LeptonJets;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    Jets AntiLeptonJets;

//     const HClonesArray *ClonesArrays;

private:

    virtual inline std::string ClassName() const {

        return ("HLepton");

    };

};

#endif
