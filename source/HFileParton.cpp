# include "HFileParton.hh"

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

    TreeName = "LHEF";

    return TreeName;

}

string hanalysis::hparton::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hanalysis::hparton::HFile::GetEvent()
{

    Print(1, "Get Event");

    return (new HEvent());

}
