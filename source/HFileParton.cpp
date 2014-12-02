# include "HFileParton.hh"

hanalysis::hparton::HFile::HFile()
{

    Print(HNotification, "Constructor");

    SetVariables();

}

hanalysis::hparton::HFile::HFile(const std::string &Process)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hanalysis::hparton::HFile::GetTreeName() const
{

    Print(HInformation, "Get Tree String");

    TreeName = "LHEF";

    return TreeName;

}

std::string hanalysis::hparton::HFile::GetFilePath() const
{

    Print(HInformation, "FilePath");

    FileSuffix = "_unweighted_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hanalysis::hparton::HFile::GetEvent()
{

    Print(HNotification, "Get Event");

    return (new HEvent());

}
