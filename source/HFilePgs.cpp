# include "HFilePgs.hh"

hpgs::HFile::HFile()
{

    Print(HNotification, "Constructor");

    SetVariables();

}

hpgs::HFile::HFile(const std::string &Process)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hpgs::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hpgs::HFile::GetTreeName() const
{

    Print(HInformation, "Get Tree String");

    TreeName = "LHCO";

    return TreeName;

}

std::string hpgs::HFile::GetFilePath() const
{

    Print(HInformation, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hpgs::HFile::GetEvent()
{

    Print(HNotification, "Get Event");

    return (new HEvent());

}
