# include "HFile.hh"

HFile::HFile()
{

    Print(0, "Constructor");

    SetVariables();

}

HFile::HFile(TString Process)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;

//     Title = Process;

}

HFile::HFile(TString Process, TString Run)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

//     Title = Process;


}

TString HFile::Title(){

    return RunFolder;

}

TString HFile::MadGraphFilePath() {

    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");

}

// TString HFile::BasePath = "$HOME/Development/madgraph/";
TString HFile::BasePath = "$HOME/Development/MadGraph/";

TString HFile::FileSuffix = "_delphes_events.root";

TString HFile::TreeString = "Delphes";

bool HFile::Snowmass = 0;

void HFile::SetVariables()
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

HFile::~HFile()
{


    Print(0, "Destructor");

}

TString HFileParton::GetTreeName()
{

    Print(1, "Get Tree String");

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

    Print(1, "Get Tree String");

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

    Print(1, "Get Tree String");

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

    Print(1, "Get Tree String");

    return TreeString;

}



TString HFileFolder::GetFilePath()
{

    Print(1, "FilePath");

    TString FlatFilePath = BasePath + ProcessFolder + FileSuffix;

//     Title = ProcessFolder;

    return FlatFilePath;

}
