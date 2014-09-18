# include "HFile.hh"

HFileBase::HFileBase()
{

    Print(0, "Constructor");

    SetVariables();

}

HFileBase::HFileBase(TString Process)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    Title = Process;

}

HFileBase::HFileBase(TString Process, TString Run)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

    Title = Process;


}

TString HFileBase::BasePath = "$HOME/Development/madgraph/";

TString HFileBase::FileSuffix = "_delphes_events.root";

TString HFileBase::TreeString = "Delphes";

void HFileBase::SetVariables()
{

    Print(1, "Set Variables");

    //     MadGraphPath = "/data/hajer/MadGraph/";
    //     MadGraphPath = "$HOME/Development/MadGraph/";
//     BasePath = "$HOME/Development/madgraph/";

    RunFolder = "run_01";

    TagString = "tag_1";

//     TreeString = "Delphes";

    Crosssection = 0;

    Error = 0;

}

HFileBase::~HFileBase()
{


    Print(0, "Destructor");

}

TString HFileParton::GetTreeName()
{

    Print(1, "Set Tree String");

    TreeString = "LHEF";

    return TreeString;

}

TString HFileParton::GetFilePath()
{

    Print(1, "FilePath");

    FileSuffix = "_unweighted_events.root";

    TString PartonFilePath = MadGraphFilePath() + TagString +  FileSuffix;

    return (PartonFilePath);

}

TString HFilePgs::GetTreeName()
{

    Print(1, "Set Tree String");

    TreeString = "LHCO";

    return TreeString;

}

TString HFilePgs::GetFilePath()
{

    Print(1, "FilePath");

    FileSuffix = "_pgs_events.root";

    TString PgsFilePath = MadGraphFilePath() + TagString +  FileSuffix;

    return PgsFilePath;

}

TString HFileDelphes::GetTreeName()
{

    Print(1, "Set Tree String");

    TreeString = "Delphes";

    return TreeString;

}

TString HFileDelphes::GetFilePath()
{

    Print(1, "FilePath");

    FileSuffix = "_delphes_events.root";

    TString DelphesFilePath = MadGraphFilePath() + TagString +  FileSuffix;

    return (DelphesFilePath);

}

TString HFileFolder::GetTreeName()
{

    Print(1, "Set Tree String");

//     TreeString = "Delphes";

    return TreeString;

}



TString HFileFolder::GetFilePath()
{

    Print(1, "FilePath");

//     FileSuffix = "_delphes_events.root";

    TString FlatFilePath = BasePath + ProcessFolder + FileSuffix;

    Title = ProcessFolder;

    return FlatFilePath;

}
