# include "HFile.hh"

hanalysis::HFile::HFile()
{
  Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
}

hanalysis::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
    RunFolder = Run;
}

std::string hanalysis::HFile::GetTitle() const
{
    return (ProcessFolder + "-" + RunFolder);
}

std::string hanalysis::HFile::GetMadGraphFilePath() const
{
    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");
}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::HFile::BasePath = "$HOME/Development/MadGraph/";
std::string hanalysis::HFile::FileSuffix = "_delphes_events.root";
std::string hanalysis::HFile::TreeName = "Delphes";

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
    Crosssection = 0;
    Error = 0;

//     ClonesArrays = NULL;
//     Event = NULL;
    ImportFile = NULL;
}

std::string hanalysis::HFile::GetTreeName() const
{
    Print(HInformation, "Get Tree String");
    return TreeName;
}


std::string hanalysis::HFile::GetFilePath() const
{

    Print(HInformation, "FilePath");

    return BasePath + ProcessFolder + FileSuffix;

}



std::shared_ptr<ExRootTreeReader> hanalysis::HFile::GetTreeReader()
{
    Print(HNotification, "Get Tree Reader", GetFilePath());

    const std::string ImportPath = GetFilePath();
    ImportFile =  new TFile(ImportPath.c_str());
    Print(HNotification, "File", ImportPath);
    const std::string ImportTreeName = GetTreeName();
    Print(HNotification, "Tree", ImportTreeName);
    return std::shared_ptr<ExRootTreeReader>(new ExRootTreeReader((TTree *)ImportFile->Get(ImportTreeName.c_str())));
}

std::shared_ptr<hanalysis::HClonesArray> hanalysis::HFile::GetClonesArrays()
{

    Print(HNotification, "Get Clones Arrays");
    if (GetTreeName() == "Delphes") {
        if (SnowMass) {
          return std::shared_ptr<HClonesArray>(new hdelphes::HClonesArraySnowmass());
        } else {
          return std::shared_ptr<HClonesArray>(new hdelphes::HClonesArray());
        }
    } else if (GetTreeName() == "LHEF") {
      return std::shared_ptr<HClonesArray>(new hparton::HClonesArray());
    } else if (GetTreeName() == "LHCO") {
      return std::shared_ptr<HClonesArray>(new hpgs::HClonesArray());
    } else {
      Print(HError, "unknown Tree String", GetTreeName());
//       return std::shared_ptr<HClonesArray>(new HClonesArray());
    }
}

std::shared_ptr<hanalysis::HEvent> hanalysis::HFile::GetEvent()
{
    Print(HNotification, "Get Event");
//     HEvent *Event;
    if (GetTreeName() == "Delphes") {
//       Event = new hdelphes::HEvent();
      return std::shared_ptr<HEvent>(new hdelphes::HEvent());
    } else if (GetTreeName() == "LHEF") {
//       Event = new hparton::HEvent();
      return std::shared_ptr<HEvent>(new hparton::HEvent());
    } else if (GetTreeName() == "LHCO") {
//       Event = new hpgs::HEvent();
      return std::shared_ptr<HEvent>(new hpgs::HEvent());
    } else {
        Print(HError, "unknown Tree String", GetTreeName());
    }
}

hanalysis::HFile::~HFile()
{
    Print(HNotification, "Destructor");
//     delete ImportTree;
//     delete TreeReader;
//     if (Event != NULL) delete Event;
//     if (ClonesArrays != NULL)  delete ClonesArrays;
    delete ImportFile;
}
