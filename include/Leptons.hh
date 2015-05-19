# pragma once

# include <algorithm>

# include "ClonesArrays.hh"
# include "FourVector.hh"

namespace analysis
{

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector
{

public:

    /**
     * @brief constructor
     *
     */
    Leptons();

    /**
     * @brief destructor
     *
     */
    virtual ~Leptons();

    void NewEvent(const ClonesArrays &clones_arrays);

    Vectors GetLeptonVectors();


    Jets GetLeptonJets();

    Jets GetTaggedJets(HJetTag &jet_tag) {
        jet_tag_ = &jet_tag;
        return GetLeptonJets(kTagging);
    };

protected:

    Jets GetLeptonJets(JetDetail jet_detail);

    /**
     * @brief Find the hardest of the light leptons
     *
     */
    virtual bool GetElectrons(JetDetail jet_detail) {
        Print(kError, "should be subclassed", jet_detail);
        return 0;
    }

    /**
     * @brief Find the hardest of the light leptons
     *
     */
    virtual bool GetMuons(JetDetail jet_detail) {
        Print(kError, "should be subclassed", jet_detail);
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

private:

    virtual inline std::string ClassName() const {
        return ("Leptons");
    }

};

}
