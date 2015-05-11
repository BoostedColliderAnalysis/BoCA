# ifndef HClonesArray_hh
# define HClonesArray_hh

#include <memory>
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

    enum Branch {kParticle, kPhoton, kElectron, kMuon, kJet, kMissingEt, kTrack, kTower, kEFlowTrack, kEflowPhoton, kEFlowNeutralHadron, kEFlowMuon, kGenJet, kScalarHt, kTau};

    std::string BranchName(const Branch branch) const {
        switch (branch) {
        case kParticle:
            return "Particle";
        case kPhoton:
            return "Photon";
        case kElectron:
            return "Electron";
        case kMuon:
            return "Muon";
        case kJet:
            return "Jet";
        case kMissingEt:
            return "MissingET";
        case kTrack:
            return "Track";
        case kTower:
            return "Tower";
        case kEFlowTrack:
            return "EFlowTrack";
        case kEflowPhoton:
            return "EFlowPhoton";
        case kEFlowNeutralHadron:
            return "EFlowNeutralHadron";
        case kEFlowMuon:
            return "EFlowMuon";
        case kGenJet:
            return "GenJet";
        case kScalarHt:
            return "ScalarHT";
        case kTau:
            return "Tau";
        default :
            return "";
        }
    }

    virtual std::vector<Branch> Branches() const {
        return {};
    }

    void UseBranches(ExRootTreeReader &tree_reader) {
        Print(kNotification, "Use Branches");
        for (const auto branch : Branches()) clones_arrays_.push_back(tree_reader.UseBranch(BranchName(branch).c_str()));
    }

    inline const TClonesArray &ClonesArray(const Branch branch) const {
//        std::vector<Branch> branches = Branches();
        if (std::find(Branches().begin(), Branches().end(), branch) == Branches().end()) Print(kError, "Not in branch");
        return *clones_arrays_.at(branch);
    }

    inline const TObject &Object(const Branch branch, const int number) const {
        return *ClonesArray(branch).At(number);
    }

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

    virtual void GetBranches(const std::shared_ptr< ExRootTreeReader > &) = 0;
    virtual void GetBranches(ExRootTreeReader &) = 0;

    inline int GetSum(const Branch branch) {
        return ClonesArray(branch).GetEntriesFast();
    }

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
        return EFlowTrackClonesArray;
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
     * @brief EFlow Tower Clones Array
     *
     */
    inline TObject &GetObject(const Branch branch, const int number) const {
        return *ClonesArray(branch).At(number);
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
        return EFlowTrackClonesArray->At(EFlowTrackNumber);
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

    /**
     * @brief Particle Clones Array
     *
     */
    inline const TClonesArray &Particle_clones_array() const {
        return *ParticleClonesArray;
    }

    /**
     * @brief Track Clones Array
     *
     */
    inline const TClonesArray &Track_clones_array() const {
        return *TrackClonesArray;
    }

    /**
     * @brief Tower Clones Array
     *
     */
    inline const TClonesArray &Tower_clones_array() const {
        return *TowerClonesArray;
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    inline const TClonesArray &EFlowTrack_clones_array() const {
        return *EFlowTrackClonesArray;
    }

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    inline const TClonesArray &EFlowTower_clones_array() const {
        return *EFlowTowerClonesArray;
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    inline const TClonesArray &GenJet_clones_array() const {
        return *GenJetClonesArray;
    }

    /**
     * @brief Jet Clones Array
     *
     */
    inline const TClonesArray &Jet_clones_array() const {
        return *JetClonesArray;
    }

    /**
     * @brief Electron Clones Array
     *
     */
    inline const TClonesArray &Electron_clones_array() const {
        return *ElectronClonesArray;
    }

    /**
     * @brief Muon Clones Array
     *
     */
    inline const TClonesArray &Muon_clones_array() const {
        return *MuonClonesArray;
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    inline const TClonesArray &MissingEt_clones_array() const {
        return *MissingEtClonesArray;
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    inline const TClonesArray &ScalarHt_clones_array() const {
        return *ScalarHtClonesArray;
    }

    /**
     * @brief Photon Clones Array
     *
     */
    inline const TClonesArray &Photon_clones_array() const {
        return *PhotonClonesArray;
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    inline const TClonesArray &EFlowPhoton_clones_array() const {
        return *EFlowPhotonClonesArray;
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline const TClonesArray &EFlowNeutralHadron_clones_array() const {
        return *EFlowNeutralHadronClonesArray;
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    inline const TClonesArray &EFlowMuon_clones_array() const {
        return *EFlowMuonClonesArray;
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline const TClonesArray &Tau_clones_array() const {
        return *TauClonesArray;
    }


protected:

    std::vector<TClonesArray *> clones_arrays_;

    /**
     * @brief Particle Clones Array
     *
     */
    TClonesArray *ParticleClonesArray = NULL;

    /**
     * @brief Track Clones Array
     *
     */
    TClonesArray *TrackClonesArray = NULL;

    /**
     * @brief Tower Clones Array
     *
     */
    TClonesArray *TowerClonesArray = NULL;

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TClonesArray *EFlowTrackClonesArray = NULL;

    /**
     * @brief EFlow Tower Clones Array
     *
     */
    TClonesArray *EFlowTowerClonesArray = NULL;

    /**
     * @brief GenJet Clones Array
     *
     */
    TClonesArray *GenJetClonesArray = NULL;

    /**
     * @brief Jet Clones Array
     *
     */
    TClonesArray *JetClonesArray = NULL;

    /**
     * @brief Electron Clones Array
     *
     */
    TClonesArray *ElectronClonesArray = NULL;

    /**
     * @brief Muon Clones Array
     *
     */
    TClonesArray *MuonClonesArray = NULL;

    /**
     * @brief Missing ET Clones Array
     *
     */
    TClonesArray *MissingEtClonesArray = NULL;

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TClonesArray *ScalarHtClonesArray = NULL;

    /**
     * @brief Photon Clones Array
     *
     */
    TClonesArray *PhotonClonesArray = NULL;

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TClonesArray *EFlowPhotonClonesArray = NULL;

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *EFlowNeutralHadronClonesArray = NULL;

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TClonesArray *EFlowMuonClonesArray = NULL;

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TClonesArray *TauClonesArray = NULL;

    ExRootTreeReader *tree_reader_;

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

    void GetBranches(const std::shared_ptr< ExRootTreeReader > &TreeReader);
    void GetBranches(ExRootTreeReader &TreeReader);

protected:



    std::vector<Branch> Branches() const {
        return {kParticle, kPhoton, kElectron, kMuon, kJet, kMissingEt, kTrack, kTower, kEFlowTrack, kEflowPhoton, kEFlowNeutralHadron, kGenJet, kScalarHt};
    }

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

    void GetBranches(const std::shared_ptr< ExRootTreeReader > &TreeReader);
    void GetBranches(ExRootTreeReader &TreeReader);

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

    void GetBranches(const std::shared_ptr< ExRootTreeReader > &TreeReader);
    void GetBranches(ExRootTreeReader &TreeReader);

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

    void GetBranches(const std::shared_ptr< ExRootTreeReader > &TreeReader);
    void GetBranches(ExRootTreeReader &TreeReader);

protected:

    inline std::string NameSpaceName() const {
        return "hparton";
    }

    inline std::string ClassName() const {
        return "HClonesArray";
    }

};

#endif
