# include "ClonesArrays.hh"

# include "TClonesArray.h"
# include "TObjArray.h"

namespace analysis {

ClonesArrays::ClonesArrays(const ClonesArrays::Source source)
{
    source_ = source;
}

std::string ClonesArrays::BranchName(const Branch branch) const
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
        Print(Severity::Error, "Unnmaed branch");
        return "";
    }
}

ClonesArrays::Source ClonesArrays::source() const
{
    return source_;
}

std::vector<ClonesArrays::Branch> ClonesArrays::Branches() const
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

void ClonesArrays::UseBranches(exroot::TreeReader &tree_reader)
{
    Print(Severity::Debug, "Use Branches");
    for (const auto & branch : Branches()) clones_arrays_[branch] = tree_reader.UseBranch(BranchName(branch).c_str());
}

TClonesArray &ClonesArrays::ClonesArray(const Branch branch) const
{
    Print(Severity::Debug, "Clones Array", BranchName(branch));
    if (!clones_arrays_.at(branch)) Print(Severity::Error, "Not in branch");
    return *clones_arrays_.at(branch);
}

TObject &ClonesArrays::Object(const ClonesArrays::Branch branch, const int number) const
{
    Print(Severity::Debug, "Object", BranchName(branch), number);
    return *ClonesArray(branch).At(number);
}

int ClonesArrays::EntrySum(const Branch branch) const
{
    Print(Severity::Debug, "Sum", BranchName(branch), ClonesArray(branch).GetEntriesFast());
    return ClonesArray(branch).GetEntriesFast();
}

}
