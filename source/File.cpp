#include "File.hh"

#include "TFile.h"
#include "TTree.h"

#include "Predicate.hh"

namespace analysis
{

File::File()
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    file_suffix_ = file_suffix();
}

File::File(const std::string &process)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    file_suffix_ = file_suffix();
}

File::File(const std::string &process, const float crosssection)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    file_suffix_ = file_suffix();
}

File::File(const std::string &process, const float crosssection, const float mass)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = mass;
    file_suffix_ = file_suffix();
}

File::File(const Strings &processes)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_ = Join(process_folders_, processes);
    file_suffix_ = file_suffix();
}

File::File(const Strings &processes, const float crosssection)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_ = Join(process_folders_, processes);
    crossection_ = crosssection;
    file_suffix_ = file_suffix();
}

File::File(const Strings &processes, const float crosssection, const float mass)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_ = Join(process_folders_, processes);
    crossection_ = crosssection;
    mass_ = mass;
    file_suffix_ = file_suffix();
}

File::File(const std::string &process, const std::string &run_folder)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    run_folder_ = run_folder;
    file_suffix_ = file_suffix();
}

File::File(const std::string &process, const std::string &base_path, const std::string &file_suffix, const float crosssection)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    crossection_ = crosssection;
}

File::File(const std::string &process, const std::string &base_path, const std::string &file_suffix)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    base_path_ = base_path;
    file_suffix_ = file_suffix;
}

File::File(const std::string &process, const std::string &base_path, const std::string &file_suffix, const std::string &nice_name)
{
    Print(Severity::debug, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    nice_name_ = nice_name;
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
        Print(Severity::error, "file suffix", "no source");
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
        Print(Severity::error, "tree name", "no tree name");
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
    Print(Severity::information, "Set Variables");
    run_folder_ = "run_01";
    tag_name_ = "tag_1";
}

Strings File::Paths() const
{
    Print(Severity::information, "FilePath");
    Strings FilePaths;
    for (const auto & process_folder : process_folders_) FilePaths.emplace_back(base_path_ + process_folder + file_suffix_);
    return FilePaths;
}

exroot::TreeReader File::TreeReader()
{
    Print(Severity::notification, "Tree Reader", Paths().front());
    chain_ = new TChain(tree_name().c_str());
    for (const auto & path : Paths()) chain_->Add(path.c_str());
    return exroot::TreeReader(chain_);
}

ClonesArrays File::clones_arrays()
{
    Print(Severity::notification, "Clones Arrays");
    return ClonesArrays(source());
}


Event File::event()
{
    Print(Severity::notification, "event");
    return Event(source());
}

File::~File()
{
    Print(Severity::debug, "Destructor");
    delete chain_;
}

}
