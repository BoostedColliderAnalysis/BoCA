# include "HFile.hh"

hanalysis::HFile::HFile()
{
    Print(kInformation, "Constructor");
    SetVariables();
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    CrosssectionM = NewCrosssection;
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection, const float NewMass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    CrosssectionM = NewCrosssection;
    MassM = NewMass;
}

hanalysis::HFile::HFile(const Strings &NewProcesses)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    MassM = 0;
}

hanalysis::HFile::HFile(const Strings &NewProcesses, const float NewCrosssection)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    CrosssectionM = NewCrosssection;
    MassM = 0;
}

hanalysis::HFile::HFile(const Strings &NewProcesses, const float NewCrosssection, const float NewMass)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    CrosssectionM = NewCrosssection;
    MassM = NewMass;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const std::string &Run)
{
    Print(kInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    RunFolder = Run;
    MassM = 0;
}

std::string hanalysis::HFile::GetTitle() const
{
    return (ProcessFolders.front() + "-" + RunFolder);
}

std::string hanalysis::HFile::GetMadGraphFilePath() const
{
    return (BasePath + ProcessFolders.front() + "/events/" + RunFolder + "/");
}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::HFile::BasePath = "$HOME/Development/MadGraph/";
std::string hanalysis::HFile::FileSuffix = "_delphes_events.root";
std::string hanalysis::HFile::TreeNameM = "Delphes";

bool hanalysis::HFile::SnowMass = 0;
void hanalysis::HFile::SetVariables()
{
    Print(kInformation, "Set Variables");
    //     MadGraphPath = "/data/hajer/MadGraph/";
    //     MadGraphPath = "$HOME/Development/MadGraph/";
//     BasePath = "$HOME/Development/madgraph/";
    RunFolder = "run_01";
    TagName = "tag_1";
//     TreeString = "Delphes";
    CrosssectionM = 1;
    ErrorM = 0;
    File = NULL;
    Chain = NULL;
}

std::string hanalysis::HFile::TreeName() const
{
    Print(kInformation, "Get Tree String");
    return TreeNameM;
}


Strings hanalysis::HFile::Paths() const
{

    Print(kInformation, "FilePath");

    Strings FilePaths;
    for (const auto & ProcessFolder : ProcessFolders)FilePaths.emplace_back(BasePath + ProcessFolders.front() + FileSuffix);

    return FilePaths;

}

ExRootTreeReader hanalysis::HFile::TreeReader()
{
    Print(kNotification, "Get Tree Reader", Paths().front());

    Chain = new TChain(TreeName().c_str());
    for (const auto & FilePath : Paths()) Chain->Add(FilePath.c_str());
    return ExRootTreeReader(Chain);
}

hanalysis::ClonesArrays &hanalysis::HFile::GetClonesArrays()
{

    Print(kNotification, "Get Clones Arrays");
    if (TreeName() == "Delphes") {
        if (SnowMass) {
            clones_array_ = new hdelphes::HClonesArraySnowmass();
        } else {
            clones_array_ =  new hdelphes::HClonesArray();
        }
    } else if (TreeName() == "LHEF") {
        clones_array_ = new hparton::HClonesArray();
    } else if (TreeName() == "LHCO") {
        clones_array_ = new hpgs::HClonesArray();
    } else {
        Print(kError, "unknown Tree String", TreeName());
    }
        return *clones_array_;
}


hanalysis::Event &hanalysis::HFile::event()
{
    Print(kNotification, "Get event");
//       Event *event;
    if (TreeName() == "Delphes") {
        event_ = new hdelphes::Event();
    } else if (TreeName() == "LHEF") {
        event_ = new hparton::Event();
    } else if (TreeName() == "LHCO") {
        event_ = new hpgs::Event();
    } else {
        Print(kError, "unknown Tree String", TreeName());
    }
    return *event_;
}

hanalysis::HFile::~HFile()
{
    Print(kNotification, "Destructor");
    delete File;
    delete Chain;
    delete event_;
    delete clones_array_;
}
