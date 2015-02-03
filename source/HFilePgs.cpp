# include "HFilePgs.hh"

hanalysis::hpgs::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::hpgs::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
}

hanalysis::hpgs::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
    RunFolder = Run;
}

std::string hanalysis::hpgs::HFile::GetTreeName() const
{
    Print(HInformation, "Get Tree String");
    TreeName = "LHCO";
    return TreeName;
}

std::string hanalysis::hpgs::HFile::GetFilePath() const
{
    Print(HInformation, "FilePath");
    FileSuffix = "_pgs_events.root";
    return GetMadGraphFilePath() + TagName +  FileSuffix;
}

std::shared_ptr<hanalysis::HEvent> hanalysis::hpgs::HFile::GetEvent()
{
    Print(HNotification, "Get Event");
    return std::shared_ptr<hanalysis::HEvent>(new HEvent());
}
