#include "ClonesArrays.hh"

#include "TClonesArray.h"
#include "TObjArray.h"
#include "Debug.hh"

namespace analysis
{

ClonesArrays::ClonesArrays(const Source source)
{
    source_ = source;
}

std::string ClonesArrays::BranchName(const Branch branch) const
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
        Error("Unnmaed branch");
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

void ClonesArrays::UseBranches(exroot::TreeReader &tree_reader)
{
    Debug("Use TreeBrancheses");
    for (const auto & branch : Branches()) clones_arrays_[branch] = tree_reader.UseBranch(BranchName(branch).c_str());
}

TClonesArray &ClonesArrays::ClonesArray(const Branch branch) const
{
    Debug("Clones Array", BranchName(branch));
    if (!clones_arrays_.at(branch)) Error("Not in branch", BranchName(branch));
    return *clones_arrays_.at(branch);
}

TObject &ClonesArrays::Object(const Branch branch, const int number) const
{
    Debug("Object", BranchName(branch), number);
    return *ClonesArray(branch).At(number);
}

int ClonesArrays::EntrySum(const Branch branch) const
{
    Debug("Sum", BranchName(branch), ClonesArray(branch).GetEntriesFast());
    return ClonesArray(branch).GetEntriesFast();
}

}
