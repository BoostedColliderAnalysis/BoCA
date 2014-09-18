# ifndef HClonesArray_hh
# define HClonesArray_hh

# include "TClonesArray.h"

# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"

/**
 * @brief small class loading the Branches into ClonesArrays
 *
 */
class HClonesArrayBase : public HObject
{

public:

    /**
     * @brief Constructor
     *
     * @param TreeReader ExRoot TreeReader
     */
    HClonesArrayBase();

    /**
     * @brief Destructor
     *
     */
    ~HClonesArrayBase();

    void ResetBranches();

    virtual void UseBranches(ExRootTreeReader *) = 0;

    /**
     * @brief Particle Clones Array
     *
     */
    TClonesArray *ParticleClonesArray;

    /**
     * @brief Track Clones Array
     *
     */
    TClonesArray *TrackClonesArray;

    /**
     * @brief Tower Clones Array
     *
     */
    TClonesArray *TowerClonesArray;

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TClonesArray *EFlowTrackClonesArray;

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    TClonesArray *EFlowTowerClonesArray;

    /**
     * @brief GenJet Clones Array
     *
     */
    TClonesArray *GenJetClonesArray;

    /**
     * @brief Jet Clones Array
     *
     */
    TClonesArray *JetClonesArray;

    /**
     * @brief Electron Clones Array
     *
     */
    TClonesArray *ElectronClonesArray;

    /**
     * @brief Muon Clones Array
     *
     */
    TClonesArray *MuonClonesArray;

    /**
     * @brief Missing ET Clones Array
     *
     */
    TClonesArray *MissingEtClonesArray;

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TClonesArray *ScalarHtClonesArray;

    /**
     * @brief Photon Clones Array
     *
     */
    TClonesArray *PhotonClonesArray;

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TClonesArray *EFlowPhotonClonesArray;

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *EFlowNeutralHadronClonesArray;

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TClonesArray *EFlowMuonClonesArray;

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *TauClonesArray;

private:

    virtual TString ClassName() {
        return ("HClonesArrayBase");
    };

};

class HClonesArrayDelphes : public HClonesArrayBase
{

    void UseBranches(ExRootTreeReader *);

private:

    virtual TString ClassName() {
        return ("HClonesArrayDelphes");
    };

};

class HClonesArraySnowmass : public HClonesArrayBase
{

    void UseBranches(ExRootTreeReader *);

private:

    virtual TString ClassName() {
        return ("HClonesArraySnowmass");
    };

};

class HClonesArrayPgs : public HClonesArrayBase
{

    void UseBranches(ExRootTreeReader *);

private:

    virtual TString ClassName() {
        return ("HClonesArrayPgs");
    };

};

class HClonesArrayParton : public HClonesArrayBase
{

    void UseBranches(ExRootTreeReader *);

private:

    virtual TString ClassName() {
        return ("HClonesArrayParton");
    };

};

#endif
