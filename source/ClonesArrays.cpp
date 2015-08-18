/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "ClonesArrays.hh"

#include "TClonesArray.h"
#include "TObjArray.h"
#include "exroot/ExRootAnalysis.hh"
#include "Debug.hh"

namespace analysis {

ClonesArrays::ClonesArrays() {}

ClonesArrays::ClonesArrays(Source source)
{
    source_ = source;
}

std::string ClonesArrays::BranchName(Branch branch) const
{
    switch (branch) {
    case Branch::particle:
        return "Particle";
    case Branch::photon:
        return "Photon";
    case Branch::electron:
        return "Electron";
    case Branch::muon:
        return "Muon";
    case Branch::jet:
        return "Jet";
    case Branch::missing_et:
        return "MissingET";
    case Branch::track:
        return "Track";
    case Branch::tower:
        return "Tower";
    case Branch::e_flow_track:
        return "EFlowTrack";
    case Branch::e_flow_photon:
        return "EFlowPhoton";
    case Branch::e_flow_neutral_hadron:
        return "EFlowNeutralHadron";
    case Branch::e_flow_muon:
        return "EFlowMuon";
    case Branch::gen_jet:
        return "GenJet";
    case Branch::scalar_ht:
        return "ScalarHT";
    case Branch::tau:
        return "Tau";
    default :
        Error("Unnamed branch");
        return "";
    }
}

Source ClonesArrays::source() const
{
    return source_;
}

std::vector<Branch> ClonesArrays::Branches() const
{
    switch (source()) {
    case Source::delphes :
        return {Branch::particle, Branch::photon, Branch::electron, Branch::muon, Branch::jet, Branch::missing_et, Branch::track, Branch::tower, Branch::e_flow_track, Branch::e_flow_photon, Branch::e_flow_neutral_hadron, Branch::gen_jet, Branch::scalar_ht};
    case Source::pgs:
        return {};
    case Source::parton:
        return {};
    default :
        return {};
    }
}

void ClonesArrays::UseBranches(exroot::TreeReader& tree_reader)
{
    Debug("Use TreeBrancheses");
    for (auto const& branch : Branches()) clones_arrays_[branch] = tree_reader.UseBranch(BranchName(branch).c_str());
}

TClonesArray& ClonesArrays::ClonesArray(Branch branch) const
{
    Debug("Clones Array", BranchName(branch));
    if (!clones_arrays_.at(branch)) Error("Not in branch", BranchName(branch));
    return *clones_arrays_.at(branch);
}

TObject& ClonesArrays::Object(Branch branch, int number) const
{
    Debug("Object", BranchName(branch), number);
    if (!ClonesArray(branch).At(number)) Error("Not in branch", BranchName(branch));
    return *ClonesArray(branch).At(number);
}

int ClonesArrays::EntrySum(Branch branch) const
{
    Debug("Sum", BranchName(branch), ClonesArray(branch).GetEntriesFast());
    return ClonesArray(branch).GetEntriesFast();
}

}
