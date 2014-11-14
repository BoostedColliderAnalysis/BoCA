# include "HFileParton.hh"

hparton::HFile::HFile()
{

    Print(HNotification, "Constructor");

    SetVariables();

}

hparton::HFile::HFile(const std::string &Process)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hparton::HFile::GetTreeName() const
{

    Print(HInformation, "Get Tree String");

    TreeName = "LHEF";

    return TreeName;

}

std::string hparton::HFile::GetFilePath() const
{

    Print(HInformation, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hparton::HFile::GetEvent()
{

    Print(HNotification, "Get Event");

    return (new HEvent());

}
