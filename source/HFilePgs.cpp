# include "HFilePgs.hh"

hpgs::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hpgs::HFile::HFile(const std::string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hpgs::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hpgs::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    TreeName = "LHCO";

    return TreeName;

}

std::string hpgs::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hpgs::HFile::GetEvent()
{

    Print(1, "Get Event");

    return (new HEvent());

}
