# include "File.hh"

# include "TFile.h"
# include "TTree.h"

# include "Predicate.hh"


analysis::File::File()
{
    Print(kInformation, "Constructor");
    SetVariables();
    file_suffix_ = file_suffix();
}

analysis::File::File(const std::string &process)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    file_suffix_ = file_suffix();
}

analysis::File::File(const std::string &process, const float crosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    file_suffix_ = file_suffix();
}

analysis::File::File(const std::string &process, const float crosssection, const float mass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = mass;
    file_suffix_ = file_suffix();
}

analysis::File::File(const Strings &processes)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_ = JoinVectors(process_folders_, processes);
    file_suffix_ = file_suffix();
}

analysis::File::File(const Strings &processes, const float crosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_ = JoinVectors(process_folders_, processes);
    crossection_ = crosssection;
    file_suffix_ = file_suffix();
}

analysis::File::File(const Strings &processes, const float crosssection, const float mass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_ = JoinVectors(process_folders_, processes);
    crossection_ = crosssection;
    mass_ = mass;
    file_suffix_ = file_suffix();
}

analysis::File::File(const std::string &process, const std::string &run_folder)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    run_folder_ = run_folder;
    file_suffix_ = file_suffix();
}

analysis::File::File(const std::string &process, const std::string &base_path, const std::string &file_suffix)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    base_path_ = base_path;
    file_suffix_ = file_suffix;
}

std::string analysis::File::file_suffix() const
{
    switch (source()) {
    case ClonesArrays::kDelphes :
        return "_delphes_events.root";
    case ClonesArrays::kParton :
        return "_unweighted_events.root";
    case ClonesArrays::kPgs :
        return "_pgs_events.root";
    default :
        Print(kError, "file suffix", "no source");
        return "";
    }
}

std::string analysis::File::tree_name() const
{
    switch (source()) {
    case ClonesArrays::kDelphes :
        return "Delphes";
    case ClonesArrays::kParton :
        return "LHEF";
    case ClonesArrays::kPgs :
        return "LHCO";
    default :
        Print(kError, "tree name", "no tree name");
        return "";
    }
}

std::string analysis::File::Title() const
{
    return process_folders_.front() + "-" + run_folder_;
}

std::string analysis::File::MadGraphFilePath() const
{
    return base_path_ + process_folders_.front() + "/events/" + run_folder_ + "/";
}

void analysis::File::SetVariables()
{
    Print(kInformation, "Set Variables");
    run_folder_ = "run_01";
    tag_name_ = "tag_1";
}

Strings analysis::File::Paths() const
{
    Print(kInformation, "FilePath");
    Strings FilePaths;
    for (const auto & process_folder : process_folders_) FilePaths.emplace_back(base_path_ + process_folder + file_suffix_);
    return FilePaths;
}

ExRootTreeReader analysis::File::TreeReader()
{
    Print(kNotification, "Get Tree Reader", Paths().front());
    chain_ = new TChain(tree_name().c_str());
    for (const auto & path : Paths()) chain_->Add(path.c_str());
    return ExRootTreeReader(chain_);
}

analysis::ClonesArrays analysis::File::clones_arrays()
{
    Print(kNotification, "Get Clones Arrays");
    return ClonesArrays(source());
}


analysis::Event analysis::File::event()
{
    Print(kNotification, "Get event");
    return Event(source());
}

analysis::File::~File()
{
    Print(kNotification, "Destructor");
    delete chain_;
}
