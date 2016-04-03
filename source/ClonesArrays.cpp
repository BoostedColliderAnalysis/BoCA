/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "TreeReader.hh"
#include "ClonesArrays.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

std::string Name(Branch branch) const
{
    DEBUG0;
    switch (branch) {
    case Branch::particle : return "Particle";
    case Branch::photon : return "Photon";
    case Branch::electron : return "Electron";
    case Branch::muon : return "Muon";
    case Branch::jet : return "Jet";
    case Branch::missing_et : return "MissingET";
    case Branch::track : return "Track";
    case Branch::tower : return "Tower";
    case Branch::e_flow_track : return "EFlowTrack";
    case Branch::e_flow_photon : return "EFlowPhoton";
    case Branch::e_flow_neutral_hadron : return "EFlowNeutralHadron";
    case Branch::e_flow_muon : return "EFlowMuon";
    case Branch::gen_jet : return "GenJet";
    case Branch::scalar_ht : return "ScalarHT";
    case Branch::tau : return "Tau";
        DEFAULT(to_int(branch), "");
    }
}

ClonesArrays::ClonesArrays() {}

ClonesArrays::ClonesArrays(Source source)
{
    source_ = source;
}

Source ClonesArrays::source() const
{
    DEBUG0;
    return source_;
}

std::vector<Branch> ClonesArrays::Branches() const
{
    DEBUG0;
    switch (source()) {
    case Source::delphes : return {Branch::particle, Branch::photon, Branch::electron, Branch::muon, Branch::jet, Branch::missing_et, Branch::track, Branch::tower, Branch::e_flow_track, Branch::e_flow_photon, Branch::e_flow_neutral_hadron, Branch::gen_jet, Branch::scalar_ht};
    case Source::pgs: return {Branch::photon, Branch::electron, Branch::muon, Branch::jet, Branch::missing_et, Branch::gen_jet, Branch::tau};
    case Source::parton: return {Branch::particle};
        DEFAULT(to_int(source), {});
    }
}

void ClonesArrays::UseBranches(exroot::TreeReader& tree_reader)
{
    DEBUG0;
    for (auto const & branch : Branches()) clones_arrays_.emplace(branch, tree_reader.UseBranch(Name(branch).c_str()));
}

auto& ClonesArrays::ClonesArray(Branch branch) const
{
    DEBUG(Name(branch));
    if (!IsSet(branch)) ERROR("Not in branch", Name(branch));
    NOTE("clones_arrays_.at(branch)");
    return *clones_arrays_.at(branch);
}

TObject& ClonesArrays::Object(Branch branch, int number) const
{
    DEBUG(Name(branch), number);
    if (!ClonesArray(branch).At(number))ERROR("Not in branch", Name(branch));
    return *ClonesArray(branch).At(number);
}

int ClonesArrays::EntrySum(Branch branch) const
{
    DEBUG(Name(branch), ClonesArray(branch).GetEntriesFast());
    return ClonesArray(branch).GetEntriesFast();
}

bool ClonesArrays::IsSet(Branch branch) const
{
    return clones_arrays_.find(branch) != clones_arrays_.end();
}

}

