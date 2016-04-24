
#include "boca/delphes/Classes.hh"
#include "boca/exroot/Classes.hh"

#include "boca/generic/Types.hh"
#include "boca/io/TreeReader.hh"
#include "boca/Branches.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

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
      DEFAULT(to_int(branch), "");
    }
  }

std::string Name(Source source)
{
  switch (source) {
    case Source::delphes : return "Delphes";
    case Source::pgs : return "PGS";
    case Source::parton : return "Parton";
    case Source::tagger : return "Tagger";
    DEFAULT(to_int(source), "");
  }
}

TreeReader::TreeReader(std::vector<std::string> const& paths, std::string const& tree_name, Source source)
{
    INFO(tree_name, paths.front());
    source_ = source;
    tree_name_ = tree_name;
    paths_ = paths;
    Initialize();
}

TreeReader::TreeReader(std::string const& path, std::string const& tree_name, Source source)
{
    INFO(tree_name, path);
    source_ = source;
    tree_name_ = tree_name;
    paths_ = {path};
    Initialize();
}


TreeReader::TreeReader(const TreeReader& tree_reader)
{
    source_ = tree_reader.source_;
    tree_name_ = tree_reader.tree_name_;
    paths_ = tree_reader.paths_;
//     generator_arrays_ = tree_reader.generator_arrays_;
    tagger_arrays_ = tree_reader.tagger_arrays_;
    Initialize();
}

void TreeReader::Initialize()
{
    for (auto const & path : paths_) chain_.AddFile(path.c_str(), TChain::kBigNumber, tree_name_.c_str());
    tree_reader_.SetTree(&chain_);
    NewElements();
}

long TreeReader::GetEntries() const
{
    INFO0;
    return tree_reader_.GetEntries(true);
}

bool TreeReader::ReadEntry(long number)
{
    INFO(number);
    auto valid = tree_reader_.SetEntry(number) == TTreeReader::kEntryValid;
    CHECK(valid, "not a valid entry in tree reader", number);
    for (auto & pair : generator_arrays_) valid = valid && pair.second->ProxyRead() == ROOT::TTreeReaderArrayBase::kReadSuccess;
    CHECK(valid, "not a valid entry in tree reader generator array", number);
    for (auto & pair : tagger_arrays_) valid = valid && pair.second->ProxyRead() == ROOT::TTreeReaderArrayBase::kReadSuccess;
    CHECK(valid, "not a valid entry in tree reader tagger array", number);
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
    case Source::tagger : break;
    DEFAULT(to_int(source_));
    }
}

bool TreeReader::Has(Branch branch) const
{
    INFO(Name(branch));
    return generator_arrays_.find(branch) != generator_arrays_.end();
}

bool TreeReader::Has(std::string const& name) const
{
    INFO(name);
    return tagger_arrays_.find(name) != tagger_arrays_.end();
}

void TreeReader::NewBase(std::string name, TClass & cl) {
    if (Has(name)) std::cout << name << " exists already, will be overwritten" << tagger_arrays_.size() << std::endl;
    tagger_arrays_.emplace(name, std::make_shared<TreeReaderArray>(tree_reader_, name, cl));
}

TreeReaderArray& TreeReader::Array(std::string const& name) const {
    if (!Has(name)) std::cout << name << " does not exist " << tagger_arrays_.size() << std::endl;
    return const_cast<TreeReaderArray &>(*std::dynamic_pointer_cast<TreeReaderArray>(tagger_arrays_.at(name)).get());
}

TreeReaderArray& TreeReader::Array(std::string const& name, TClass & cl) {
    if (!Has(name)) tagger_arrays_.emplace(name, std::make_shared<TreeReaderArray>(tree_reader_, name, cl));
    return const_cast<TreeReaderArray &>(*std::dynamic_pointer_cast<TreeReaderArray>(tagger_arrays_.at(name)).get());
}

TChain & TreeReader::Chain()
{
  return chain_;
}

}

