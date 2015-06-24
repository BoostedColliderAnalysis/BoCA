# pragma once

# include "TObject.h"

# include  "exroot/ExRootAnalysis.hh"
# include "Object.hh"

namespace analysis {

/**
 * @brief Base class for loading the Branches into ClonesArrays
 *
 */
class ClonesArrays : public Object
{

public:

    enum Source {kDelphes, kPgs, kParton};

    ClonesArrays(const Source source);

    enum Branch {kParticle, kPhoton, kElectron, kMuon, kJet, kMissingEt, kTrack, kTower, kEFlowTrack, kEflowPhoton, kEFlowNeutralHadron, kEFlowMuon, kGenJet, kScalarHt, kTau};

    std::string BranchName(const Branch branch) const;

    Source source() const;

    std::vector<Branch> Branches() const;

    void UseBranches(exroot::TreeReader &tree_reader);

    TClonesArray &ClonesArray(const Branch branch) const;

    TObject &Object(const Branch branch, const int number) const;

    int EntrySum(const Branch branch) const;

     int ParticleSum() const {
        return EntrySum(kParticle);
    }

     int TrackSum() const {
        return EntrySum(kTrack);
    }

     int TowerSum() const {
        return EntrySum(kTower);
    }

     int EFlowTrackSum() const {
        return EntrySum(kEFlowTrack);
    }

     int GenJetSum() const {
        return EntrySum(kGenJet);
    }

     int JetSum() const {
        return EntrySum(kJet);
    }

     int ElectronSum() const {
        return EntrySum(kElectron);
    }

     int MuonSum() const {
        return EntrySum(kMuon);
    }

     int PhotonSum() const {
        return EntrySum(kPhoton);
    }

     int EFlowPhotonSum() const {
        return EntrySum(kEflowPhoton);
    }

     int EFlowNeutralHadronSum() const {
        return EntrySum(kEFlowNeutralHadron);
    }

     int EFlowMuonSum() const {
        return EntrySum(kEFlowMuon);
    }

     int TauSum() const {
        return EntrySum(kTau);
    }

    /**
     * @brief Particle Clones Array
     *
     */
     TClonesArray &ParticleClonesArray() const {
        return ClonesArray(kParticle);
    }

    /**
     * @brief Electron Clones Array
     *
     */
     TClonesArray &ElectronClonesArray() const {
        return ClonesArray(kElectron);
    }

    /**
     * @brief Muon Clones Array
     *
     */
     TClonesArray &MuonClonesArray() const {
        return ClonesArray(kMuon);
    }

    /**
     * @brief Photon Clones Array
     *
     */
     TClonesArray &PhotonClonesArray() const {
        return ClonesArray(kPhoton);
    }

    /**
     * @brief Particle Clones Array
     *
     */
     TObject &Particle(const int number) const {
        return Object(kParticle, number);
    }

    /**
     * @brief Track Clones Array
     *
     */
     TObject &Track(const int number) const {
        return Object(kTrack, number);
    }

    /**
     * @brief Tower Clones Array
     *
     */
     TObject &Tower(const int number) const {
        return Object(kTower, number);
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
     TObject &EFlowTrack(const int number) const {
        return Object(kEFlowTrack, number);
    }

    /**
     * @brief GenJet Clones Array
     *
     */
     TObject &GenJet(const int number) const {
        return Object(kGenJet, number);
    }

    /**
     * @brief Jet Clones Array
     *
     */
     TObject &Jet(const int number) const {
        return Object(kJet, number);
    }

    /**
     * @brief Electron Clones Array
     *
     */
     TObject &Electron(const int number) const {
        return Object(kElectron, number);
    }

    /**
     * @brief Muon Clones Array
     *
     */
     TObject &Muon(const int number) const {
        return Object(kMuon, number);
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
     TObject &MissingEt() const {
        return Object(kMissingEt, 0);
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
     TObject &ScalarHt() const {
        return Object(kScalarHt, 0);
    }

    /**
     * @brief Photon Clones Array
     *
     */
     TObject &Photon(const int number) const {
        return Object(kPhoton, number);
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
     TObject &EFlowPhoton(const int number) const {
        return Object(kEflowPhoton, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
     TObject &EFlowNeutralHadron(const int number) const {
        return Object(kEFlowNeutralHadron, number);
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
     TObject &EFlowMuon(const int number) const {
        return Object(kEFlowMuon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
     TObject &Tau(const int number) const {
        return Object(kTau, number);
    }

protected:


    virtual  std::string ClassName() const {
        return "ClonesArrays";
    }

private:

    std::map<Branch, TClonesArray *> clones_arrays_;

    Source source_;

};

}
