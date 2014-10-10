# include "HFile.hh"

HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

HFile::HFile(const string Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

HFile::HFile(const string Process, const string Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string HFile::Title() const {

    return RunFolder;

}

string HFile::MadGraphFilePath() const {

    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");

}

// TString HFile::BasePath = "$HOME/Development/madgraph/";
string HFile::BasePath = "$HOME/Development/MadGraph/";

string HFile::FileSuffix = "_delphes_events.root";

string HFile::TreeString = "Delphes";

bool HFile::Snowmass = 0;

void HFile::SetVariables()
{

    Print(2, "Set Variables");

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


    Print(1, "Destructor");

}

string HFileParton::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHEF";

    return TreeString;

}

string HFileParton::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}

string HFilePgs::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHCO";

    return TreeString;

}

string HFilePgs::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}

string HFileDelphes::GetTreeName() const
{

    Print(2, "Get Tree String");

    return "Delphes";

}

string HFileDelphes::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_delphes_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}

string HFileFolder::GetTreeName() const
{

    Print(2, "Get Tree String");

    return TreeString;
}


string HFileFolder::GetFilePath() const
{

    Print(2, "FilePath");

    return (BasePath + ProcessFolder + FileSuffix);

}
