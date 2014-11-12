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
class hanalysis::HClonesArray : public HObject
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

    virtual void GetBranches(const ExRootTreeReader *const) = 0;

    int GetParticleSum() const {
        return ParticleClonesArray->GetEntriesFast();
    };

    int GetTrackSum() const {
        return TrackClonesArray->GetEntriesFast();
    };

    int GetTowerSum() const {
        return TowerClonesArray->GetEntriesFast();
    };

    int GetEFlowTrackSum() const {
        return EFlowTrackClonesArray->GetEntriesFast();
    };

    int GetEFlowTowerSum() const {
        return EFlowTowerClonesArray->GetEntriesFast();
    };

    int GetGenJetSum() const {
        return GenJetClonesArray->GetEntriesFast();
    };

    int GetJetSum() const {
        return JetClonesArray->GetEntriesFast();
    };

    int GetElectronSum() const {
        return ElectronClonesArray->GetEntriesFast();
    };

    int GetMuonSum() const {
        return MuonClonesArray->GetEntriesFast();
    };

    int GetMissingEtSum() const {
        return MissingEtClonesArray->GetEntriesFast();
    };

    int ScalarHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    };

    int GetPhotonSum() const {
        return PhotonClonesArray->GetEntriesFast();
    };

    int GetEFlowPhotonSum() const {
        return EFlowPhotonClonesArray->GetEntriesFast();
    };

    int GetEFlowNeutralHadronSum() const {
        return EFlowNeutralHadronClonesArray->GetEntriesFast();
    };

    int GetEFlowMuonSum() const {
        return EFlowMuonClonesArray->GetEntriesFast();
    };

    int GetTauSum() const {
        return TauClonesArray->GetEntriesFast();
    };

    int GetScalerHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    };

    /**
     * @brief Particle Clones Array
     *
     */
    TClonesArray *GetParticleClonesArray() const {
        return ParticleClonesArray;
    };

    /**
     * @brief Track Clones Array
     *
     */
    TClonesArray *GetTrackClonesArray() const {
        return TrackClonesArray;
    };

    /**
     * @brief Tower Clones Array
     *
     */
    TClonesArray *GetTowerClonesArray() const {
        return TowerClonesArray;
    };

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TClonesArray *GetEFlowTrackClonesArray() const {
        return EFlowTowerClonesArray;
    };

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    TClonesArray *GetEFlowTowerClonesArray() const {
        return EFlowTowerClonesArray;
    };

    /**
     * @brief GenJet Clones Array
     *
     */
    TClonesArray *GetGenJetClonesArray() const {
        return GenJetClonesArray;
    };

    /**
     * @brief Jet Clones Array
     *
     */
    TClonesArray *GetJetClonesArray() const {
        return JetClonesArray;
    };

    /**
     * @brief Electron Clones Array
     *
     */
    TClonesArray *GetElectronClonesArray() const {
        return ElectronClonesArray;
    };

    /**
     * @brief Muon Clones Array
     *
     */
    TClonesArray *GetMuonClonesArray() const {
        return MuonClonesArray;
    };

    /**
     * @brief Missing ET Clones Array
     *
     */
    TClonesArray *GetMissingEtClonesArray() const {
        return MissingEtClonesArray;
    };

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TClonesArray *GetScalarHtClonesArray() const {
        return ScalarHtClonesArray;
    };

    /**
     * @brief Photon Clones Array
     *
     */
    TClonesArray *GetPhotonClonesArray() const {
        return PhotonClonesArray;
    };

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TClonesArray *GetEFlowPhotonClonesArray() const {
        return EFlowPhotonClonesArray;
    };

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *GetEFlowNeutralHadronClonesArray() const {
        return EFlowNeutralHadronClonesArray;
    };

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TClonesArray *GetEFlowMuonClonesArray() const {
        return EFlowMuonClonesArray;
    };

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *GetTauClonesArray() const {
        return TauClonesArray;
    };

    /**
     * @brief Particle Clones Array
     *
     */
    TObject *GetParticle(const int ParticleNumber) const {
        return ParticleClonesArray->At(ParticleNumber);
    };

    /**
     * @brief Track Clones Array
     *
     */
    TObject *GetTrack(const int TrackNumber) const {
        return TrackClonesArray->At(TrackNumber);
    };

    /**
     * @brief Tower Clones Array
     *
     */
    TObject *GetTower(const int TowerNumber) const {
        return TowerClonesArray->At(TowerNumber);
    };

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TObject *GetEFlowTrack(const int EFlowTrackNumber) const {
        return EFlowTowerClonesArray->At(EFlowTrackNumber);
    };

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    TObject *GetEFlowTower(const int EFlowTowerNumber) const {
        return EFlowTowerClonesArray->At(EFlowTowerNumber);
    };

    /**
     * @brief GenJet Clones Array
     *
     */
    TObject *GetGenJet(const int GenJetNumber) const {
        return GenJetClonesArray->At(GenJetNumber);
    };

    /**
     * @brief Jet Clones Array
     *
     */
    TObject *GetJet(const int JetNumber) const {
        return JetClonesArray->At(JetNumber);
    };

    /**
     * @brief Electron Clones Array
     *
     */
    TObject *GetElectron(const int ElectronNumber) const {
        return ElectronClonesArray->At(ElectronNumber);
    };

    /**
     * @brief Muon Clones Array
     *
     */
    TObject *GetMuon(const int MuonNumber) const {
        return MuonClonesArray->At(MuonNumber);
    };

    /**
     * @brief Missing ET Clones Array
     *
     */
    TObject *GetMissingEt() const {
        return MissingEtClonesArray->At(0);
    };

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TObject *GetScalarHt() const {
        return ScalarHtClonesArray->At(0);
    };

    /**
     * @brief Photon Clones Array
     *
     */
    TObject *GetPhoton(const int PhotonNumber) const {
        return PhotonClonesArray->At(PhotonNumber);
    };

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TObject *GetEFlowPhoton(const int EFlowPhotonNumber) const {
        return EFlowPhotonClonesArray->At(EFlowPhotonNumber);
    };

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject *GetEFlowNeutralHadron(const int EFlowNeutralHadronNumber) const {
        return EFlowNeutralHadronClonesArray->At(EFlowNeutralHadronNumber);
    };

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TObject *GetEFlowMuon(const int EFlowMuonNumber) const {
        return EFlowMuonClonesArray->At(EFlowMuonNumber);
    };

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject *GetTau(const int TauNumber) const {
        return TauClonesArray->At(TauNumber);
    };


protected:

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

    virtual inline std::string ClassName() const {

        return "HClonesArray";

    };

};

/**
 * @brief Clonesarray subclass for delphes files
 *
 */
class hdelphes::HClonesArray : public hanalysis::HClonesArray
{

public:


    /**
     * @brief Constructor
     *
     */
    HClonesArray();

    void GetBranches(const ExRootTreeReader *const);

protected:

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HClonesArray";
    };

};

/**
 * @brief ClonesArray subclass for Scnowmass files
 *
 */
class hdelphes::HClonesArraySnowmass : public HClonesArray
{

public:


    /**
     * @brief Constructor
     *
     */
    HClonesArraySnowmass();

    void GetBranches(const ExRootTreeReader *const);

protected:

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HClonesArraySnowmass";
    };

};

/**
 * @brief ClonesArray subclass for Pgs files
 *
 */
class hpgs::HClonesArray : public hanalysis::HClonesArray
{

public:

    /**
     * @brief Constructor
     *
     */
    HClonesArray();

    void GetBranches(const ExRootTreeReader *const);

protected:

    inline std::string NameSpaceName() const {
        return "HPgs";
    }

    inline std::string ClassName() const {

        return "HClonesArray";

    };

};

/**
 * @brief ClonesArray Subclass for unweighted MadGraph files
 *
 */
class hparton::HClonesArray : public hanalysis::HClonesArray
{

public:

    /**
     * @brief Constructor
     *
     */
    HClonesArray();

    void GetBranches(const ExRootTreeReader *const);

protected:

    inline std::string NameSpaceName() const {
        return "HParton";
    }

    inline std::string ClassName() const {

        return "HClonesArray";

    };

};

#endif
