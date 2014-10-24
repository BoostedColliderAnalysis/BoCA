# include "HFile.hh"

Analysis::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

Analysis::HFile::HFile(const string Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

Analysis::HFile::HFile(const string Process, const string Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string Analysis::HFile::Title() const {

    return RunFolder;

}

string Analysis::HFile::MadGraphFilePath() const {

    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");

}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
string Analysis::HFile::BasePath = "$HOME/Development/MadGraph/";

string Analysis::HFile::FileSuffix = "_delphes_events.root";

string Analysis::HFile::TreeString = "Delphes";

bool Analysis::HFile::Snowmass = 0;

void Analysis::HFile::SetVariables()
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

Analysis::HFile::~HFile()
{


    Print(1, "Destructor");

}

HParton::HFile::HFile()
{

  Print(1, "Constructor");

  SetVariables();

}

HParton::HFile::HFile(const string Process)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

}

HParton::HFile::HFile(const string Process, const string Run)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

  RunFolder = Run;

}

string HParton::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHEF";

    return TreeString;

}

string HParton::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}


HPgs::HFile::HFile()
{

  Print(1, "Constructor");

  SetVariables();

}

HPgs::HFile::HFile(const string Process)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

}

HPgs::HFile::HFile(const string Process, const string Run)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

  RunFolder = Run;

}

string HPgs::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHCO";

    return TreeString;

}

string HPgs::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}

Analysis::HDelphes::HFile::HFile()
{

  Print(1, "Constructor");

  SetVariables();

}

Analysis::HDelphes::HFile::HFile(const string Process)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

}

Analysis::HDelphes::HFile::HFile(const string Process, const string Run)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

  RunFolder = Run;

}

string Analysis::HDelphes::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    return "Delphes";

}

string Analysis::HDelphes::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_delphes_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}


Analysis::HFileFolder::HFileFolder()
{

  Print(1, "Constructor");

  SetVariables();

}

Analysis::HFileFolder::HFileFolder(const string Process)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

}

Analysis::HFileFolder::HFileFolder(const string Process, const string Run)
{

  Print(1, "Constructor");

  SetVariables();

  ProcessFolder = Process;

  RunFolder = Run;

}

string Analysis::HFileFolder::GetTreeName() const
{

    Print(2, "Get Tree String");

    return TreeString;
}


string Analysis::HFileFolder::GetFilePath() const
{

    Print(2, "FilePath");

    return (BasePath + ProcessFolder + FileSuffix);

}
