
#include "delphes/Delphes.hh"
#include "exroot/ExRootAnalysis.hh"

#include "TreeReader.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

std::string Name(Branch branch)
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
        DEFAULT("Branch", "");
    }
}

std::mutex TreeReader::mutex_;

TreeReader::TreeReader(TChain& chain)
{
    INFO0;
    source_ = Source::delphes;
    chain_ = &chain;
    NewElements();
    std::lock_guard<std::mutex> guard(mutex_);
    tree_reader_.SetTree(chain_);
}

TreeReader::TreeReader(std::vector<std::string> const& paths, std::string const& tree_name)
{
  INFO(tree_name, paths.front());
  source_ = Source::delphes;
  for (auto const & path : paths) chain_2_.AddFile(path.c_str(), TChain::kBigNumber, tree_name.c_str());
  NewElements();
  std::lock_guard<std::mutex> guard(mutex_);
  tree_reader_.SetTree(&chain_2_);
}

long TreeReader::GetEntries() const
{
    INFO0;
    std::lock_guard<std::mutex> guard(mutex_);
    return tree_reader_.GetEntries(false);
}

bool TreeReader::ReadEntry(long number)
{
  INFO(number);
    std::lock_guard<std::mutex> guard(mutex_);
    bool valid = tree_reader_.SetEntry(number) == TTreeReader::kEntryValid;
    CHECK(valid, "not a valid entry", number);
    if(!valid) return valid;
    for (auto & pair : map_) pair.second->Fill();
    return valid;
}

void TreeReader::NewElements()
{
    INFO0;
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
    case Source::pgs :
        NewElement<exroot::Photon>(Branch::photon);
        NewElement<exroot::Electron>(Branch::electron);
        NewElement<exroot::Muon>(Branch::muon);
        NewElement<exroot::Jet>(Branch::jet);
        NewElement<exroot::MissingET>(Branch::missing_et);
        NewElement<exroot::GenJet>(Branch::gen_jet);
        NewElement<exroot::Tau>(Branch::tau);
        break;
    case Source::parton :
        NewElement<exroot::GenParticle>(Branch::particle);
        break;
    default : break;
    }
}

bool TreeReader::Has(Branch branch) const
{
    INFO(boca::Name(branch));
    return map_.find(branch) != map_.end();
}
std::string Name(Source source)
{
    switch (source) {
    case Source::delphes : return "Delphes";
    case Source::pgs : return "PGS";
    case Source::parton : return "Parton";
        DEFAULT("Source", "");
    }
}

}
