# include "RootFile.hh"

# include "TFile.h"
# include "TTree.h"

# include "ClonesArrays.hh"

# include "HEventParton.hh"
# include "HEventPgs.hh"
# include "HEventDelphes.hh"

hanalysis::RootFile::RootFile()
{
    Print(kInformation, "Constructor");
    SetVariables();
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const float crosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const float crosssection, const float mass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = mass;
}

hanalysis::RootFile::RootFile(const Strings &processes)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const Strings &processes, const float crosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    crossection_ = crosssection;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const Strings &processes, const float crosssection, const float mass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    crossection_ = crosssection;
    mass_ = mass;
}

hanalysis::RootFile::RootFile(const std::string &process, const std::string &run_folder)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    run_folder_ = run_folder;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const std::string &base_path, const std::string &file_suffix)
{
    Print(kInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    mass_ = 0;
}

std::string hanalysis::RootFile::GetTitle() const
{
    return process_folders_.front() + "-" + run_folder_;
}

std::string hanalysis::RootFile::GetMadGraphFilePath() const
{
    return base_path_ + process_folders_.front() + "/events/" + run_folder_ + "/";
}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::RootFile::base_path_ = "$HOME/Development/MadGraph/";
std::string hanalysis::RootFile::file_suffix_ = "_delphes_events.root";
std::string hanalysis::RootFile::tree_name_ = "Delphes";

bool hanalysis::RootFile::snow_mass_ = 0;
void hanalysis::RootFile::SetVariables()
{
    Print(kInformation, "Set Variables");
    //     MadGraphPath = "/data/hajer/MadGraph/";
    //     MadGraphPath = "$HOME/Development/MadGraph/";
//     BasePath = "$HOME/Development/madgraph/";
    run_folder_ = "run_01";
    tag_name_ = "tag_1";
//     TreeString = "Delphes";
    crossection_ = 1;
    crosssection_error_ = 0;
}

std::string hanalysis::RootFile::tree_name() const
{
    Print(kInformation, "Get Tree String");
    return tree_name_;
}


Strings hanalysis::RootFile::Paths() const
{
    Print(kInformation, "FilePath");
    Strings FilePaths;
    for (const auto & ProcessFolder : process_folders_)FilePaths.emplace_back(base_path_ + process_folders_.front() + file_suffix_);
    return FilePaths;
}

ExRootTreeReader hanalysis::RootFile::TreeReader()
{
    Print(kNotification, "Get Tree Reader", Paths().front());
    chain_ = new TChain(tree_name().c_str());
    for (const auto & FilePath : Paths()) chain_->Add(FilePath.c_str());
    return ExRootTreeReader(chain_);
}

hanalysis::ClonesArrays hanalysis::RootFile::GetClonesArrays()
{
    Print(kNotification, "Get Clones Arrays");
    if (tree_name() == "Delphes") {
        if (snow_mass_) {
//             clones_array_ = new ClonesArrays(k);
        } else {
            return ClonesArrays(ClonesArrays::Source::kDelphes);
        }
    } else if (tree_name() == "LHEF") {
        return ClonesArrays(ClonesArrays::Source::kParton);
    } else if (tree_name() == "LHCO") {
        return ClonesArrays(ClonesArrays::Source::kPgs);
    } else {
        Print(kError, "unknown Tree String", tree_name());
    }
}


hanalysis::Event &hanalysis::RootFile::event()
{
    Print(kNotification, "Get event");
    if (tree_name() == "Delphes") {
        event_ = new hdelphes::Event();
    } else if (tree_name() == "LHEF") {
        event_ = new hparton::Event();
    } else if (tree_name() == "LHCO") {
        event_ = new hpgs::Event();
    } else {
        Print(kError, "unknown Tree String", tree_name());
    }
    return *event_;
}

hanalysis::RootFile::~RootFile()
{
    Print(kNotification, "Destructor");
    delete chain_;
    delete event_;
}
