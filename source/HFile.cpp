# include "HFile.hh"

hanalysis::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    CrosssectionM = NewCrosssection;
    MassM = 0;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection, const float NewMass)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.emplace_back(NewProcess);
    CrosssectionM = NewCrosssection;
    MassM = NewMass;
}

hanalysis::HFile::HFile(const Strings &NewProcesses)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    MassM = 0;
}

hanalysis::HFile::HFile(const Strings &NewProcesses, const float NewCrosssection)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    CrosssectionM = NewCrosssection;
    MassM = 0;
}

hanalysis::HFile::HFile(const Strings &NewProcesses, const float NewCrosssection, const float NewMass)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
    CrosssectionM = NewCrosssection;
    MassM = NewMass;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const std::string &Run)
{
    Print(HInformation, "Constructor");
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
    return (BasePath + ProcessFolders.front() + "/Events/" + RunFolder + "/");
}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::HFile::BasePath = "$HOME/Development/MadGraph/";
std::string hanalysis::HFile::FileSuffix = "_delphes_events.root";
std::string hanalysis::HFile::TreeNameM = "Delphes";

bool hanalysis::HFile::SnowMass = 0;
void hanalysis::HFile::SetVariables()
{
    Print(HInformation, "Set Variables");
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
    Print(HInformation, "Get Tree String");
    return TreeNameM;
}


Strings hanalysis::HFile::Paths() const
{

    Print(HInformation, "FilePath");

    Strings FilePaths;
    for (const auto & ProcessFolder : ProcessFolders)FilePaths.emplace_back(BasePath + ProcessFolders.front() + FileSuffix);

    return FilePaths;

}

ExRootTreeReader hanalysis::HFile::TreeReader()
{
    Print(HNotification, "Get Tree Reader", Paths().front());

    Chain = new TChain(TreeName().c_str());
    for (const auto & FilePath : Paths()) Chain->Add(FilePath.c_str());
    return ExRootTreeReader(Chain);
}

hanalysis::ClonesArrays &hanalysis::HFile::GetClonesArrays()
{

    Print(HNotification, "Get Clones Arrays");
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
        Print(HError, "unknown Tree String", TreeName());
    }
        return *clones_array_;
}


hanalysis::HEvent &hanalysis::HFile::Event()
{
    Print(HNotification, "Get Event");
//       HEvent *Event;
    if (TreeName() == "Delphes") {
        event_ = new hdelphes::HEvent();
    } else if (TreeName() == "LHEF") {
        event_ = new hparton::HEvent();
    } else if (TreeName() == "LHCO") {
        event_ = new hpgs::HEvent();
    } else {
        Print(HError, "unknown Tree String", TreeName());
    }
    return *event_;
}

hanalysis::HFile::~HFile()
{
    Print(HNotification, "Destructor");
    delete File;
    delete Chain;
    delete event_;
    delete clones_array_;
}
