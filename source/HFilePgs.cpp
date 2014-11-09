# include "HFilePgs.hh"

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

    TreeName = "LHCO";

    return TreeName;

}

string hanalysis::hpgs::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    FileSuffix = "_pgs_events.root";

    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hanalysis::hpgs::HFile::GetEvent()
{

    Print(1, "Get Event");

    return (new HEvent());

}
