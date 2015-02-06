# include "HFile.hh"

hanalysis::HFile::HFile()
{
  Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::HFile::HFile(const std::string &NewProcess)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolders.push_back(NewProcess);
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection)
{
  Print(HInformation, "Constructor");
  SetVariables();
  ProcessFolders.push_back(NewProcess);
  CrosssectionM = NewCrosssection;
}

hanalysis::HFile::HFile(const std::string &NewProcess, const float NewCrosssection, const float NewMass)
{
  Print(HInformation, "Constructor");
  SetVariables();
  ProcessFolders.push_back(NewProcess);
  CrosssectionM = NewCrosssection;
  MassM = NewMass;
}

hanalysis::HFile::HFile(const HStrings &NewProcesses)
{
  Print(HInformation, "Constructor");
  SetVariables();
  ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
}

hanalysis::HFile::HFile(const HStrings &NewProcesses, const float NewCrosssection)
{
  Print(HInformation, "Constructor");
  SetVariables();
  ProcessFolders.insert(ProcessFolders.end(), NewProcesses.begin(), NewProcesses.end());
  CrosssectionM = NewCrosssection;
}

hanalysis::HFile::HFile(const HStrings &NewProcesses, const float NewCrosssection, const float NewMass)
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
    ProcessFolders.push_back(NewProcess);
    RunFolder = Run;
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
    CrosssectionM = 0;
    ErrorM = 0;
    File = NULL;
    Chain = NULL;
}

std::string hanalysis::HFile::TreeName() const
{
    Print(HInformation, "Get Tree String");
    return TreeNameM;
}


HStrings hanalysis::HFile::Paths() const
{

    Print(HInformation, "FilePath");

    HStrings FilePaths;
    for(const auto& ProcessFolder : ProcessFolders)FilePaths.push_back(BasePath + ProcessFolders.front() + FileSuffix);

    return FilePaths;

}



std::shared_ptr<ExRootTreeReader> hanalysis::HFile::TreeReader()
{
    Print(HNotification, "Get Tree Reader", Paths().front());

//     const std::string Path = GetFilePath();
//     File =  new TFile(Path.c_str());
//     Print(HNotification, "File", Path);
//     const std::string TreeName = GetTreeName();
//     Print(HNotification, "Tree", TreeName);
//     return std::shared_ptr<ExRootTreeReader>(new ExRootTreeReader((TTree *)File->Get(TreeName.c_str())));

//     TChain Chain(GetTreeName().c_str());
    Chain = new TChain(TreeName().c_str());
    for(const auto& FilePath : Paths()) Chain->Add(FilePath.c_str());
    return std::shared_ptr<ExRootTreeReader>(new ExRootTreeReader(Chain));
}

std::shared_ptr<hanalysis::HClonesArray> hanalysis::HFile::ClonesArrays()
{

    Print(HNotification, "Get Clones Arrays");
    if (TreeName() == "Delphes") {
        if (SnowMass) {
          return std::shared_ptr<HClonesArray>(new hdelphes::HClonesArraySnowmass());
        } else {
          return std::shared_ptr<HClonesArray>(new hdelphes::HClonesArray());
        }
    } else if (TreeName() == "LHEF") {
      return std::shared_ptr<HClonesArray>(new hparton::HClonesArray());
    } else if (TreeName() == "LHCO") {
      return std::shared_ptr<HClonesArray>(new hpgs::HClonesArray());
    } else {
      Print(HError, "unknown Tree String", TreeName());
//       return std::shared_ptr<HClonesArray>(new HClonesArray());
    }
}

std::shared_ptr<hanalysis::HEvent> hanalysis::HFile::Event()
{
    Print(HNotification, "Get Event");
//     HEvent *Event;
    if (TreeName() == "Delphes") {
//       Event = new hdelphes::HEvent();
      return std::shared_ptr<HEvent>(new hdelphes::HEvent());
    } else if (TreeName() == "LHEF") {
//       Event = new hparton::HEvent();
      return std::shared_ptr<HEvent>(new hparton::HEvent());
    } else if (TreeName() == "LHCO") {
//       Event = new hpgs::HEvent();
      return std::shared_ptr<HEvent>(new hpgs::HEvent());
    } else {
        Print(HError, "unknown Tree String", TreeName());
    }
}

hanalysis::HFile::~HFile()
{
    Print(HNotification, "Destructor");
    delete File;
    delete Chain;
}
