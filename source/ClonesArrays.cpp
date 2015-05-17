# include "ClonesArrays.hh"

# include "TClonesArray.h"
# include "TObjArray.h"

analysis::ClonesArrays::ClonesArrays(const analysis::ClonesArrays::Source source)
{
    source_ = source;
}

std::string analysis::ClonesArrays::BranchName(const Branch branch) const
{
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
        Print(kError, "Unnmaed branch");
        return "";
    }
}

analysis::ClonesArrays::Source analysis::ClonesArrays::source() const
{
    return source_;
}

std::vector<analysis::ClonesArrays::Branch> analysis::ClonesArrays::Branches() const
{
    switch (source()) {
    case kDelphes :
        return {kParticle, kPhoton, kElectron, kMuon, kJet, kMissingEt, kTrack, kTower, kEFlowTrack, kEflowPhoton, kEFlowNeutralHadron, kGenJet, kScalarHt};
    case kPgs:
        return {};
    case kParton:
        return {};
    default :
        return {};
    }
}

void analysis::ClonesArrays::UseBranches(ExRootTreeReader &tree_reader)
{
    Print(kDebug, "Use Branches");
    for (const auto & branch : Branches()) clones_arrays_[branch] = tree_reader.UseBranch(BranchName(branch).c_str());
}

TClonesArray &analysis::ClonesArrays::ClonesArray(const Branch branch) const
{
    Print(kDebug, "Clones Array", BranchName(branch));
    if (!clones_arrays_.at(branch)) Print(kError, "Not in branch");
    return *clones_arrays_.at(branch);
}

TObject &analysis::ClonesArrays::Object(const analysis::ClonesArrays::Branch branch, const int number) const
{
    Print(kDebug, "Object", BranchName(branch), number);
    return *ClonesArray(branch).At(number);
}

int analysis::ClonesArrays::EntrySum(const Branch branch) const
{
    Print(kDebug, "Sum", BranchName(branch), ClonesArray(branch).GetEntriesFast());
    return ClonesArray(branch).GetEntriesFast();
}
