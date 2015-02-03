# include "HFileParton.hh"

hanalysis::hparton::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::hparton::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
}

hanalysis::hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
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
    return GetMadGraphFilePath() + TagName +  FileSuffix;
}

std::shared_ptr<hanalysis::HEvent> hanalysis::hparton::HFile::GetEvent()
{
    Print(HNotification, "Get Event");
    return std::shared_ptr<hanalysis::HEvent>(new HEvent());
}
