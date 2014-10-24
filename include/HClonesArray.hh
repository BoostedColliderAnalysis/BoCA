# ifndef HClonesArray_hh
# define HClonesArray_hh

# include "TObjArray.h"
# include "TClonesArray.h"

# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"

/**
 * @brief Base class for loading the Branches into ClonesArrays
 *
 */
class Analysis::HClonesArray : public HObject
{

public:

    /**
     * @brief Constructor
     *
     * @param TreeReader ExRoot TreeReader
     */
    HClonesArray();

    /**
     * @brief Destructor
     *
     */
    ~HClonesArray();

    void ResetBranches();

    virtual void GetBranches(const ExRootTreeReader * const) = 0;

    int ParticleSum() const {
        return ParticleClonesArray->GetEntriesFast();
    };

    int TrackSum() const {
        return TrackClonesArray->GetEntriesFast();
    };

    int TowerSum() const {
        return TowerClonesArray->GetEntriesFast();
    };

    int EFlowTrackSum() const {
        return EFlowTrackClonesArray->GetEntriesFast();
    };

    int EFlowTowerSum() const {
        return EFlowTowerClonesArray->GetEntriesFast();
    };

    int GenJetSum() const {
        return GenJetClonesArray->GetEntriesFast();
    };

    int JetSum() const {
        return JetClonesArray->GetEntriesFast();
    };

    int ElectronSum() const {
        return ElectronClonesArray->GetEntriesFast();
    };

    int MuonSum() const {
        return MuonClonesArray->GetEntriesFast();
    };

    int MissingEtSum() const {
        return MissingEtClonesArray->GetEntriesFast();
    };

    int ScalarHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    };

    int PhotonSum() const {
        return PhotonClonesArray->GetEntriesFast();
    };

    int EFlowPhotonSum() const {
        return EFlowPhotonClonesArray->GetEntriesFast();
    };

    int EFlowNeutralHadronSum() const {
        return EFlowNeutralHadronClonesArray->GetEntriesFast();
    };

    int EFlowMuonSum() const {
        return EFlowMuonClonesArray->GetEntriesFast();
    };

    int TauSum() const {
        return TauClonesArray->GetEntriesFast();
    };

    int ScalerHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    };

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

    virtual inline string ClassName() const {

        return "HClonesArray";

    };

};

/**
 * @brief Clonesarray subclass for delphes files
 *
 */
class Analysis::HDelphes::HClonesArray : public Analysis::HClonesArray
{

    void GetBranches(const ExRootTreeReader * const);

private:

    inline string ClassName() const {

        return "HDelphes: HClonesArray";

    };

};

/**
 * @brief ClonesArray subclass for Scnowmass files
 *
 */
class Analysis::HDelphes::HClonesArraySnowmass : public HClonesArray
{

    void GetBranches(const ExRootTreeReader * const);

private:

    inline string ClassName() const {

        return "HDelphes: HClonesArraySnowmass";

    };

};

/**
 * @brief ClonesArray subclass for Pgs files
 *
 */
class HPgs::HClonesArray : public Analysis::HClonesArray
{

    void GetBranches(const ExRootTreeReader * const);

private:

    inline string ClassName() const {

        return "HPgs: HClonesArray";

    };

};

/**
 * @brief ClonesArray Subclass for unweighted MadGraph files
 *
 */
class HParton::HClonesArray : public Analysis::HClonesArray
{

    void GetBranches(const ExRootTreeReader * const);

private:

    inline string ClassName() const {

        return "HParton: HClonesArray";

    };

};

#endif
