# ifndef HClonesArray_hh
# define HClonesArray_hh

# include "TObjArray.h"
# include "TObject.h"
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
     */
    HClonesArray();

    /**
     * @brief Destructor
     *
     */
    ~HClonesArray();

    virtual void GetBranches(const ExRootTreeReader *const) = 0;

    inline int GetParticleSum() const {
        return ParticleClonesArray->GetEntriesFast();
    }

    inline int GetTrackSum() const {
        return TrackClonesArray->GetEntriesFast();
    }

    inline int GetTowerSum() const {
        return TowerClonesArray->GetEntriesFast();
    }

    inline int GetEFlowTrackSum() const {
        return EFlowTrackClonesArray->GetEntriesFast();
    }

    inline int GetEFlowTowerSum() const {
        return EFlowTowerClonesArray->GetEntriesFast();
    }

    inline int GetGenJetSum() const {
        return GenJetClonesArray->GetEntriesFast();
    }

    inline int JetSum() const {
        return JetClonesArray->GetEntriesFast();
    }

    inline int GetElectronSum() const {
        return ElectronClonesArray->GetEntriesFast();
    }

    inline int GetMuonSum() const {
        return MuonClonesArray->GetEntriesFast();
    }

    inline int GetMissingEtSum() const {
        return MissingEtClonesArray->GetEntriesFast();
    }

    inline int GetScalarHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    }

    inline int GetPhotonSum() const {
        return PhotonClonesArray->GetEntriesFast();
    }

    inline int GetEFlowPhotonSum() const {
        return EFlowPhotonClonesArray->GetEntriesFast();
    }

    inline int GetEFlowNeutralHadronSum() const {
        return EFlowNeutralHadronClonesArray->GetEntriesFast();
    }

    inline int GetEFlowMuonSum() const {
        return EFlowMuonClonesArray->GetEntriesFast();
    }

    inline int GetTauSum() const {
        return TauClonesArray->GetEntriesFast();
    }

    inline int GetScalerHtSum() const {
        return ScalarHtClonesArray->GetEntriesFast();
    }

    /**
     * @brief Particle Clones Array
     *
     */
    inline TClonesArray *GetParticleClonesArray() const {
        return ParticleClonesArray;
    }

    /**
     * @brief Track Clones Array
     *
     */
    inline TClonesArray *GetTrackClonesArray() const {
        return TrackClonesArray;
    }

    /**
     * @brief Tower Clones Array
     *
     */
    inline TClonesArray *GetTowerClonesArray() const {
        return TowerClonesArray;
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    inline TClonesArray *GetEFlowTrackClonesArray() const {
        return EFlowTowerClonesArray;
    }

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    inline TClonesArray *GetEFlowTowerClonesArray() const {
        return EFlowTowerClonesArray;
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    inline TClonesArray *GetGenJetClonesArray() const {
        return GenJetClonesArray;
    }

    /**
     * @brief Jet Clones Array
     *
     */
    inline TClonesArray *GetJetClonesArray() const {
        return JetClonesArray;
    }

    /**
     * @brief Electron Clones Array
     *
     */
    inline TClonesArray *GetElectronClonesArray() const {
        return ElectronClonesArray;
    }

    /**
     * @brief Muon Clones Array
     *
     */
    inline TClonesArray *GetMuonClonesArray() const {
        return MuonClonesArray;
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    inline TClonesArray *GetMissingEtClonesArray() const {
        return MissingEtClonesArray;
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    inline TClonesArray *GetScalarHtClonesArray() const {
        return ScalarHtClonesArray;
    }

    /**
     * @brief Photon Clones Array
     *
     */
    inline TClonesArray *GetPhotonClonesArray() const {
        return PhotonClonesArray;
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    inline TClonesArray *GetEFlowPhotonClonesArray() const {
        return EFlowPhotonClonesArray;
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TClonesArray *GetEFlowNeutralHadronClonesArray() const {
        return EFlowNeutralHadronClonesArray;
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    inline TClonesArray *GetEFlowMuonClonesArray() const {
        return EFlowMuonClonesArray;
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TClonesArray *GetTauClonesArray() const {
        return TauClonesArray;
    }

    /**
     * @brief Particle Clones Array
     *
     */
    inline TObject *GetParticle(const int ParticleNumber) const {
        return ParticleClonesArray->At(ParticleNumber);
    }

    /**
     * @brief Track Clones Array
     *
     */
    inline TObject *GetTrack(const int TrackNumber) const {
        return TrackClonesArray->At(TrackNumber);
    }

    /**
     * @brief Tower Clones Array
     *
     */
    inline TObject *GetTower(const int TowerNumber) const {
        return TowerClonesArray->At(TowerNumber);
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    inline TObject *GetEFlowTrack(const int EFlowTrackNumber) const {
        return EFlowTowerClonesArray->At(EFlowTrackNumber);
    }

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    inline TObject *GetEFlowTower(const int EFlowTowerNumber) const {
        return EFlowTowerClonesArray->At(EFlowTowerNumber);
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    inline TObject *GetGenJet(const int GenJetNumber) const {
        return GenJetClonesArray->At(GenJetNumber);
    }

    /**
     * @brief Jet Clones Array
     *
     */
    inline TObject *Jet(const int JetNumber) const {
        return JetClonesArray->At(JetNumber);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    inline TObject *GetElectron(const int ElectronNumber) const {
        return ElectronClonesArray->At(ElectronNumber);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    inline TObject *GetMuon(const int MuonNumber) const {
        return MuonClonesArray->At(MuonNumber);
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    inline TObject *GetMissingEt() const {
        return MissingEtClonesArray->At(0);
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    inline TObject *GetScalarHt() const {
        return ScalarHtClonesArray->At(0);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    inline TObject *GetPhoton(const int PhotonNumber) const {
        return PhotonClonesArray->At(PhotonNumber);
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    inline TObject *GetEFlowPhoton(const int EFlowPhotonNumber) const {
        return EFlowPhotonClonesArray->At(EFlowPhotonNumber);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TObject *GetEFlowNeutralHadron(const int EFlowNeutralHadronNumber) const {
        return EFlowNeutralHadronClonesArray->At(EFlowNeutralHadronNumber);
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    inline TObject *GetEFlowMuon(const int EFlowMuonNumber) const {
        return EFlowMuonClonesArray->At(EFlowMuonNumber);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TObject *GetTau(const int TauNumber) const {
        return TauClonesArray->At(TauNumber);
    }


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

    inline std::string NameSpaceName() const {
        return "hanalysis";
    }

    virtual inline std::string ClassName() const {
        return "HClonesArray";
    }

};

/**
 * @brief Clonesarray subclass for delphes files
 *
 */
class hanalysis::hdelphes::HClonesArray : public hanalysis::HClonesArray
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
        return "hdelphes";
    }

    inline std::string ClassName() const {
        return "HClonesArray";
    }

};

/**
 * @brief ClonesArray subclass for Scnowmass files
 *
 */
class hanalysis::hdelphes::HClonesArraySnowmass : public hanalysis::HClonesArray
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
        return "hdelphes";
    }

    inline std::string ClassName() const {
        return "HClonesArraySnowmass";
    }

};

/**
 * @brief ClonesArray subclass for Pgs files
 *
 */
class hanalysis::hpgs::HClonesArray : public hanalysis::HClonesArray
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
        return "hpgs";
    }

    inline std::string ClassName() const {
        return "HClonesArray";
    }

};

/**
 * @brief ClonesArray Subclass for unweighted MadGraph files
 *
 */
class hanalysis::hparton::HClonesArray : public hanalysis::HClonesArray
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
        return "hparton";
    }

    inline std::string ClassName() const {
        return "HClonesArray";
    }

};

#endif
