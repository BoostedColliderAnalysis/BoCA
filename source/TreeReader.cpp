
#include "delphes/Delphes.hh"
#include "exroot/ExRootAnalysis.hh"

#include "TreeReader.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

std::string BranchName(Branch branch)
{
    Info0;
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
        Default("Branch", "");
    }
}

std::mutex TreeReader::mutex_;

// TreeReader::TreeReader(Strings paths, std::string tree_name) : chain_(new TChain())
// {
//     Info(tree_name, paths.size());
//     tree_name_ = tree_name;
//     paths_ = paths;
//     source_ = Source::delphes;
// }

TreeReader::TreeReader(TChain & chain)
{
//   Info(tree_name, paths.size());
  chain_ = &chain;
  source_ = Source::delphes;
// }
//
// void TreeReader::Initialize()
// {
//     Info0;
    NewElements();
    std::lock_guard<std::mutex> guard(mutex_);
//     if (paths_.size()) Info(tree_name_, paths_.front());
//     for (auto const & path : paths_) chain().AddFile(path.c_str(), TChain::kBigNumber, tree_name_.c_str());
    tree_reader_.SetTree(chain_);
//     Error(GetEntries());
}

// TChain& TreeReader::chain()
// {
//     Info0;
//     return *chain_;
// }

long TreeReader::GetEntries() const
{
    Info0;
    std::lock_guard<std::mutex> guard(mutex_);
    return tree_reader_.GetEntries(false);
}

bool TreeReader::ReadEntry(long number)
{
    Info(number);
    std::lock_guard<std::mutex> guard(mutex_);
    bool good = tree_reader_.SetEntry(number) == TTreeReader::kEntryValid;
    for (auto & pair : map) pair.second->Fill();
    return good;
}

void TreeReader::NewElements()
{
    switch (source_) {
    case Source::delphes :
        NewElement<delphes::GenParticle>(Branch::particle);
        NewElement<delphes::Electron>(Branch::electron);
        NewElement<delphes::Muon>(Branch::muon);
        NewElement<delphes::Photon>(Branch::photon);
        NewElement<delphes::Jet>(Branch::jet);
        NewElement<delphes::MissingET>(Branch::missing_et);
        NewElement<delphes::Track>(Branch::track);
        NewElement<delphes::Tower>(Branch::tower);
        NewElement<delphes::Track>(Branch::e_flow_track);
        NewElement<delphes::Tower>(Branch::e_flow_photon);
        NewElement<delphes::Tower>(Branch::e_flow_neutral_hadron);
        NewElement<delphes::Jet>(Branch::gen_jet);
        NewElement<delphes::ScalarHT>(Branch::scalar_ht);
        break;
    default : break;
    }
}

// std::vector<Branch> TreeReader::Branches() const
// {
//     Info0;
//     switch (source()) {
//     case Source::delphes : return {Branch::particle, Branch::photon, Branch::electron, Branch::muon, Branch::jet, Branch::missing_et, Branch::track, Branch::tower, Branch::e_flow_track, Branch::e_flow_photon, Branch::e_flow_neutral_hadron, Branch::gen_jet, Branch::scalar_ht};
//     case Source::pgs : return {Branch::photon, Branch::electron, Branch::muon, Branch::jet, Branch::missing_et, Branch::gen_jet, Branch::tau};
//     case Source::parton : return {Branch::particle};
//         Default("Source", {});
//     }
// }

}
