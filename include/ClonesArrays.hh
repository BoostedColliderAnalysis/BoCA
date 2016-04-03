/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>
#include <map>
#include "ClonesArray.hh"

class TreeReader;
namespace exroot
{
typedef ::TreeReader TreeReader;
}
class TClonesArray;
class TObject;

namespace boca
{

enum class Branch
{
    particle,
    photon,
    electron,
    muon,
    jet,
    missing_et,
    track,
    tower,
    e_flow_track,
    e_flow_photon,
    e_flow_neutral_hadron,
    e_flow_muon,
    gen_jet,
    scalar_ht,
    tau
};

std::string Name(Branch branch) const;

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

    ClonesArrays(Source source);

    Source source() const;

    std::vector<Branch> Branches() const;

    void UseBranches(exroot::TreeReader& tree_reader);

    auto& ClonesArray(Branch branch) const;

    TObject& Object(Branch branch, int number) const;

    int EntrySum(Branch branch) const;

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
    TClonesArray& ParticleClonesArray() const {
        return ClonesArray(Branch::particle);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    TClonesArray& ElectronClonesArray() const {
        return ClonesArray(Branch::electron);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    TClonesArray& MuonClonesArray() const {
        return ClonesArray(Branch::muon);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    TClonesArray& PhotonClonesArray() const {
        return ClonesArray(Branch::photon);
    }

    /**
     * @brief Particle Clones Array
     *
     */
    TObject& Particle(int number) const {
        return Object(Branch::particle, number);
    }

    /**
     * @brief Track Clones Array
     *
     */
    TObject& Track(int number) const {
        return Object(Branch::track, number);
    }

    /**
     * @brief Tower Clones Array
     *
     */
    TObject& Tower(int number) const {
        return Object(Branch::tower, number);
    }

    /**
     * @brief EFlow Track Clones Array
     *
     */
    TObject& EFlowTrack(int number) const {
        return Object(Branch::e_flow_track, number);
    }

    /**
     * @brief GenJet Clones Array
     *
     */
    TObject& GenJet(int number) const {
        return Object(Branch::gen_jet, number);
    }

    /**
     * @brief Jet Clones Array
     *
     */
    TObject& Jet(int number) const {
        return Object(Branch::jet, number);
    }

    /**
     * @brief Electron Clones Array
     *
     */
    TObject& Electron(int number) const {
        return Object(Branch::electron, number);
    }

    /**
     * @brief Muon Clones Array
     *
     */
    TObject& Muon(int number) const {
        return Object(Branch::muon, number);
    }

    /**
     * @brief Missing ET Clones Array
     *
     */
    TObject& MissingEt() const {
        return Object(Branch::missing_et, 0);
    }

    /**
     * @brief Scalar HT Clones Array
     *
     */
    TObject& ScalarHt() const {
        return Object(Branch::scalar_ht, 0);
    }

    /**
     * @brief Photon Clones Array
     *
     */
    TObject& Photon(int number) const {
        return Object(Branch::photon, number);
    }

    /**
     * @brief EFlow Photon Clones Array
     *
     */
    TObject& EFlowPhoton(int number) const {
        return Object(Branch::e_flow_photon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject& EFlowNeutralHadron(int number) const {
        return Object(Branch::e_flow_neutral_hadron, number);
    }

    /**
     * @brief EFlow Muon Clones Array
     *
     */
    TObject& EFlowMuon(int number) const {
        return Object(Branch::e_flow_muon, number);
    }

    /**
     * @brief EFlow Neutral Hadron Clones Array
     *
     */
    TObject& Tau(int number) const {
        return Object(Branch::tau, number);
    }

private:

    bool IsSet(Branch branch) const;

    std::map<Branch, TClonesArray*> clones_arrays_;

    Source source_;

};

}
