# include "HFile.hh"

hanalysis::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hanalysis::HFile::HFile(const string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::HFile::HFile(const string &Process, const string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string hanalysis::HFile::Title() const
{

    return RunFolder;

}

string hanalysis::HFile::MadGraphFilePath() const
{

    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");

}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
string hanalysis::HFile::BasePath = "$HOME/Development/MadGraph/";

string hanalysis::HFile::FileSuffix = "_delphes_events.root";

string hanalysis::HFile::TreeString = "Delphes";

bool hanalysis::HFile::Snowmass = 0;

void hanalysis::HFile::SetVariables()
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



string hanalysis::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    return TreeString;
}


string hanalysis::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    return (BasePath + ProcessFolder + FileSuffix);

}



ExRootTreeReader *hanalysis::HFile::GetTreeReader()
{

    Print(1, "Get Tree Reader", GetFilePath());

    // Import file
    const string ImportPath = GetFilePath();
//   TFile * const
    ImportFile = new TFile(ImportPath.c_str());
    //     TFile ImportFile = TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    const string ImportTreeName = GetTreeName();
//   TTree * const
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
    //     TTree ImportTree = (TTree)ImportFile.Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    ExRootTreeReader *const TreeReader = new ExRootTreeReader(ImportTree);

    return TreeReader;

}

hanalysis::HClonesArray *hanalysis::HFile::GetClonesArrays() const
{

    Print(1, "Get Clones Arrays");

    HClonesArray *ClonesArrays;

    if (GetTreeName() == "Delphes") {

        if (Snowmass) {

            ClonesArrays = new hdelphes::HClonesArraySnowmass();

        } else {

            ClonesArrays = new hdelphes::HClonesArray();

        }

    } else if (GetTreeName() == "LHEF") {

        ClonesArrays = new hparton::HClonesArray();

    } else if (GetTreeName() == "LHCO") {

        ClonesArrays = new hpgs::HClonesArray();

    } else {

        Print(0, "unknown Tree String", GetTreeName());

    }

    return ClonesArrays;

}

hanalysis::HEvent *hanalysis::HFile::GetEvent() const
{

    Print(1, "Get Event");

    HEvent *Event;

    if (GetTreeName() == "Delphes") {

        Event = new hdelphes::HEvent();

    } else if (GetTreeName() == "LHEF") {

        Event = new hparton::HEvent();

    } else if (GetTreeName() == "LHCO") {

        Event = new hpgs::HEvent();

    } else {

        Print(0, "unknown Tree String", GetTreeName());

    }

    return Event;

}



hanalysis::HFile::~HFile()
{

    Print(1, "Destructor");

    delete ImportFile;
    delete ImportTree;

}

hanalysis::hparton::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hanalysis::hparton::HFile::HFile(const string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::hparton::HFile::HFile(const string &Process, const string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string hanalysis::hparton::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHEF";

    return TreeString;

}

string hanalysis::hparton::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}


hanalysis::hpgs::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hanalysis::hpgs::HFile::HFile(const string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::hpgs::HFile::HFile(const string &Process, const string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string hanalysis::hpgs::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeString = "LHCO";

    return TreeString;

}

string hanalysis::hpgs::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}

hanalysis::hdelphes::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hanalysis::hdelphes::HFile::HFile(const string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::hdelphes::HFile::HFile(const string &Process, const string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

string hanalysis::hdelphes::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    return "Delphes";

}

string hanalysis::hdelphes::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_delphes_events.root";

    return (MadGraphFilePath() + TagString +  FileSuffix);

}
