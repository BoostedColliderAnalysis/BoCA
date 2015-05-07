# include "RootFile.hh"

# include "TFile.h"
# include "TTree.h"

# include "ClonesArrays.hh"

# include "HEventParton.hh"
# include "HEventPgs.hh"
# include "HEventDelphes.hh"

hanalysis::RootFile::RootFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const float crosssection)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const float crosssection, const float mass)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    crossection_ = crosssection;
    mass_ = mass;
}

hanalysis::RootFile::RootFile(const Strings &processes)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const Strings &processes, const float crosssection)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    crossection_ = crosssection;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const Strings &processes, const float crosssection, const float mass)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.insert(process_folders_.end(), processes.begin(), processes.end());
    crossection_ = crosssection;
    mass_ = mass;
}

hanalysis::RootFile::RootFile(const std::string &process, const std::string &run_folder)
{
    Print(HInformation, "Constructor");
    SetVariables();
    process_folders_.emplace_back(process);
    run_folder_ = run_folder;
    mass_ = 0;
}

hanalysis::RootFile::RootFile(const std::string &process, const std::string &base_path, const std::string &file_suffix)
{
  Print(HInformation, "Constructor");
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
    return base_path_ + process_folders_.front() + "/Events/" + run_folder_ + "/";
}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::RootFile::base_path_ = "$HOME/Development/MadGraph/";
std::string hanalysis::RootFile::file_suffix_ = "_delphes_events.root";
std::string hanalysis::RootFile::tree_name_ = "Delphes";

bool hanalysis::RootFile::snow_mass_ = 0;
void hanalysis::RootFile::SetVariables()
{
    Print(HInformation, "Set Variables");
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
    Print(HInformation, "Get Tree String");
    return tree_name_;
}


Strings hanalysis::RootFile::Paths() const
{
    Print(HInformation, "FilePath");
    Strings FilePaths;
    for (const auto & ProcessFolder : process_folders_)FilePaths.emplace_back(base_path_ + process_folders_.front() + file_suffix_);
    return FilePaths;
}

ExRootTreeReader hanalysis::RootFile::TreeReader()
{
    Print(HNotification, "Get Tree Reader", Paths().front());
    chain_ = new TChain(tree_name().c_str());
    for (const auto & FilePath : Paths()) chain_->Add(FilePath.c_str());
    return ExRootTreeReader(chain_);
}

hanalysis::ClonesArrays &hanalysis::RootFile::GetClonesArrays()
{
    Print(HNotification, "Get Clones Arrays");
    if (tree_name() == "Delphes") {
        if (snow_mass_) {
            clones_array_ = new hdelphes::HClonesArraySnowmass();
        } else {
            clones_array_ =  new hdelphes::HClonesArray();
        }
    } else if (tree_name() == "LHEF") {
        clones_array_ = new hparton::HClonesArray();
    } else if (tree_name() == "LHCO") {
        clones_array_ = new hpgs::HClonesArray();
    } else {
        Print(HError, "unknown Tree String", tree_name());
    }
    return *clones_array_;
}


hanalysis::HEvent &hanalysis::RootFile::Event()
{
    Print(HNotification, "Get Event");
    if (tree_name() == "Delphes") {
        event_ = new hdelphes::HEvent();
    } else if (tree_name() == "LHEF") {
        event_ = new hparton::HEvent();
    } else if (tree_name() == "LHCO") {
        event_ = new hpgs::HEvent();
    } else {
        Print(HError, "unknown Tree String", tree_name());
    }
    return *event_;
}

hanalysis::RootFile::~RootFile()
{
    Print(HNotification, "Destructor");
    delete chain_;
    delete event_;
    delete clones_array_;
}
