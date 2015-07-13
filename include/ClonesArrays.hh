#pragma once

// #include "TObject.h"

#include "exroot/ExRootAnalysis.hh"


namespace analysis
{

enum class Branch
{
    particle, photon, electron, muon, jet, missing_et, track, tower, e_flow_track, e_flow_photon, e_flow_neutral_hadron, e_flow_muon, gen_jet, scalar_ht, tau
};

enum class Source
{
    delphes, pgs, parton
};

/**
 * @brief Base class for loading the TreeBrancheses into ClonesArrays
 *
 */
class ClonesArrays
{

public:

    ClonesArrays();

    ClonesArrays(const Source source);

    std::string BranchName(const Branch branch) const;

    Source source() const;

    std::vector<Branch> Branches() const;

    void UseBranches(exroot::TreeReader &tree_reader);

    TClonesArray &ClonesArray(const Branch branch) const;

    TObject &Object(const analysis::Branch branch, const int number) const;

    int EntrySum(const Branch branch) const;

    int ParticleSum() const {
        return EntrySum(Branch::particle);
    }

    int TrackSum() const {
        return EntrySum(Branch::track);
    }

    int TowerSum() const {
        return EntrySum(Branch::tower);
    }

    int EFlowTrackSum() const {
        return EntrySum(Branch::e_flow_track);
    }

    int GenJetSum() const {
        return EntrySum(Branch::gen_jet);
    }

    int JetSum() const {
        return EntrySum(Branch::jet);
    }

    int ElectronSum() const {
        return EntrySum(Branch::electron);
    }

    int MuonSum() const {
        return EntrySum(Branch::muon);
    }

    int PhotonSum() const {
        return EntrySum(Branch::photon);
    }

    int EFlowPhotonSum() const {
        return EntrySum(Branch::e_flow_photon);
    }

    int EFlowNeutralHadronSum() const {
        return EntrySum(Branch::e_flow_neutral_hadron);
    }

    int EFlowMuonSum() const {
        return EntrySum(Branch::e_flow_muon);
    }

    int TauSum() const {
        return EntrySum(Branch::tau);
    }

    /**
     * @brief Particle Clones Array
     *
     */
    TClonesArray &ParticleClonesArray() const {
        return ClonesArray(Branch::particle);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    TClonesArray &ElectronClonesArray() const {
        return ClonesArray(Branch::electron);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    TClonesArray &MuonClonesArray() const {
        return ClonesArray(Branch::muon);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    TClonesArray &PhotonClonesArray() const {
        return ClonesArray(Branch::photon);
    }

    /**
     * @brief Particle Clones Array
     *
     */
    TObject &Particle(const int number) const {
        return Object(Branch::particle, number);
    }

    /**
     * @brief Track Clones Array
     *
     */
    TObject &Track(const int number) const {
        return Object(Branch::track, number);
    }

    /**
     * @brief Tower Clones Array
     *
     */
    TObject &Tower(const int number) const {
        return Object(Branch::tower, number);
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TObject &EFlowTrack(const int number) const {
        return Object(Branch::e_flow_track, number);
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    TObject &GenJet(const int number) const {
        return Object(Branch::gen_jet, number);
    }

    /**
     * @brief Jet Clones Array
     *
     */
    TObject &Jet(const int number) const {
        return Object(Branch::jet, number);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    TObject &Electron(const int number) const {
        return Object(Branch::electron, number);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    TObject &Muon(const int number) const {
        return Object(Branch::muon, number);
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    TObject &MissingEt() const {
        return Object(Branch::missing_et, 0);
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TObject &ScalarHt() const {
        return Object(Branch::scalar_ht, 0);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    TObject &Photon(const int number) const {
        return Object(Branch::photon, number);
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TObject &EFlowPhoton(const int number) const {
        return Object(Branch::e_flow_photon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject &EFlowNeutralHadron(const int number) const {
        return Object(Branch::e_flow_neutral_hadron, number);
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TObject &EFlowMuon(const int number) const {
        return Object(Branch::e_flow_muon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject &Tau(const int number) const {
        return Object(Branch::tau, number);
    }

private:

    std::map<Branch, TClonesArray *> clones_arrays_;

    Source source_;

};

}
