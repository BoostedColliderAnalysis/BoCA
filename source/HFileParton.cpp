# include "HFileParton.hh"

hparton::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hparton::HFile::HFile(const std::string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hparton::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeName = "LHEF";

    return TreeName;

}

std::string hparton::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hparton::HFile::GetEvent()
{

    Print(1, "Get Event");

    return (new HEvent());

}
