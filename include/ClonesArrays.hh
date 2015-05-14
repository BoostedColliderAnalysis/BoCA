# pragma once

# include "TObject.h"
# include "ExRootAnalysis/ExRootTreeReader.h"
# include "HObject.hh"

/**
 * @brief Base class for loading the Branches into ClonesArrays
 *
 */
class hanalysis::ClonesArrays : public HObject
{

public:

    enum Source {kDelphes, kPgs, kParton};

    ClonesArrays(const Source source);

    enum Branch {kParticle, kPhoton, kElectron, kMuon, kJet, kMissingEt, kTrack, kTower, kEFlowTrack, kEflowPhoton, kEFlowNeutralHadron, kEFlowMuon, kGenJet, kScalarHt, kTau};

    std::string BranchName(const Branch branch) const;

    Source source() const;

    std::vector<Branch> Branches() const;

    void UseBranches(ExRootTreeReader &tree_reader);

    TClonesArray &ClonesArray(const Branch branch) const;

    TObject &Object(const Branch branch, const int number) const;

    int EntrySum(const Branch branch) const;

    inline int ParticleSum() const {
        return EntrySum(kParticle);
    }

    inline int TrackSum() const {
        return EntrySum(kTrack);
    }

    inline int TowerSum() const {
        return EntrySum(kTower);
    }

    inline int EFlowTrackSum() const {
        return EntrySum(kEFlowTrack);
    }

    inline int GenJetSum() const {
        return EntrySum(kGenJet);
    }

    inline int JetSum() const {
        return EntrySum(kJet);
    }

    inline int ElectronSum() const {
        return EntrySum(kElectron);
    }

    inline int MuonSum() const {
        return EntrySum(kMuon);
    }

    inline int PhotonSum() const {
        return EntrySum(kPhoton);
    }

    inline int EFlowPhotonSum() const {
        return EntrySum(kEflowPhoton);
    }

    inline int EFlowNeutralHadronSum() const {
        return EntrySum(kEFlowNeutralHadron);
    }

    inline int EFlowMuonSum() const {
        return EntrySum(kEFlowMuon);
    }

    inline int TauSum() const {
        return EntrySum(kTau);
    }

    /**
     * @brief Particle Clones Array
     *
     */
    inline TClonesArray &ParticleClonesArray() const {
        return ClonesArray(kParticle);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    inline TClonesArray &ElectronClonesArray() const {
        return ClonesArray(kElectron);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    inline TClonesArray &MuonClonesArray() const {
        return ClonesArray(kMuon);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    inline TClonesArray &PhotonClonesArray() const {
        return ClonesArray(kPhoton);
    }

    /**
     * @brief Particle Clones Array
     *
     */
    inline TObject &Particle(const int number) const {
        return Object(kParticle, number);
    }

    /**
     * @brief Track Clones Array
     *
     */
    inline TObject &Track(const int number) const {
        return Object(kTrack, number);
    }

    /**
     * @brief Tower Clones Array
     *
     */
    inline TObject &Tower(const int number) const {
        return Object(kTower, number);
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    inline TObject &EFlowTrack(const int number) const {
        return Object(kEFlowTrack, number);
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    inline TObject &GenJet(const int number) const {
        return Object(kGenJet, number);
    }

    /**
     * @brief Jet Clones Array
     *
     */
    inline TObject &Jet(const int number) const {
        return Object(kJet, number);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    inline TObject &Electron(const int number) const {
        return Object(kElectron, number);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    inline TObject &Muon(const int number) const {
        return Object(kMuon, number);
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    inline TObject &MissingEt() const {
        return Object(kMissingEt, 0);
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    inline TObject &ScalarHt() const {
        return Object(kScalarHt, 0);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    inline TObject &Photon(const int number) const {
        return Object(kPhoton, number);
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    inline TObject &EFlowPhoton(const int number) const {
        return Object(kEflowPhoton, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TObject &EFlowNeutralHadron(const int number) const {
        return Object(kEFlowNeutralHadron, number);
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    inline TObject &EFlowMuon(const int number) const {
        return Object(kEFlowMuon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    inline TObject &Tau(const int number) const {
        return Object(kTau, number);
    }

protected:


    virtual inline std::string ClassName() const {
        return "ClonesArrays";
    }

private:

    std::map<Branch, TClonesArray *> clones_arrays_;

    Source source_;

};
