#include "File.hh"

#include "TFile.h"
#include "TTree.h"

#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

  File::File(const Strings& processes, const std::string& base_path, const std::string& file_suffix, const std::string& nice_name, float crosssection, float mass)
{
  Debug();
  SetVariables();
  process_folders_ = processes;
  base_path_ = base_path;
  file_suffix_ = file_suffix;
  crosssection_ = crosssection;
  nice_name_ = nice_name;
  mass_ = mass;
}

std::string File::file_suffix() const
{
    switch (source()) {
    case Source::delphes :
        return "_delphes_events.root";
    case Source::parton :
        return "_unweighted_events.root";
    case Source::pgs :
        return "_pgs_events.root";
    default :
        Error("file suffix", "no source");
        return "";
    }
}

std::string File::tree_name() const
{
    switch (source()) {
    case Source::delphes :
        return "Delphes";
    case Source::parton :
        return "LHEF";
    case Source::pgs :
        return "LHCO";
    default :
        Error("tree name", "no tree name");
        return "";
    }
}

std::string File::Title() const
{
    return process_folders_.front() + "-" + run_folder_;
}

std::string File::MadGraphFilePath() const
{
    return base_path_ + process_folders_.front() + "/events/" + run_folder_ + "/";
}

void File::SetVariables()
{
    Info();
    run_folder_ = "run_01";
    tag_name_ = "tag_1";
}

Strings File::Paths() const
{
    Info();
    Strings FilePaths;
    for (const auto& process_folder : process_folders_) FilePaths.emplace_back(base_path_ + process_folder + file_suffix_);
    return FilePaths;
}

exroot::TreeReader File::TreeReader()
{
    for(const auto path : Paths()) Note(path);
    chain_ = new TChain(tree_name().c_str());
    for (const auto& path : Paths()) chain_->Add(path.c_str());
    return exroot::TreeReader(chain_);
}

ClonesArrays File::clones_arrays()
{
    Info();
    return ClonesArrays(source());
}

Event File::event()
{
    Info();
    return Event(source());
}

File::~File()
{
    Debug();
    delete chain_;
}

}
