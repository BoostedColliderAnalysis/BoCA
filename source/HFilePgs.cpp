# include "HFilePgs.hh"

hanalysis::hpgs::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::hpgs::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
}

hanalysis::hpgs::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
//     RunFolder = Run;
}

std::string hanalysis::hpgs::HFile::TreeName() const
{
    Print(HInformation, "Get Tree String");
    TreeNameM = "LHCO";
    return TreeNameM;
}

HStrings hanalysis::hpgs::HFile::Paths() const
{
    Print(HInformation, "FilePath");
    FileSuffix = "_pgs_events.root";
    HStrings FilePaths;
    FilePaths.push_back(GetMadGraphFilePath() + TagName +  FileSuffix);
    return FilePaths;
}

std::shared_ptr<hanalysis::HEvent> hanalysis::hpgs::HFile::Event()
{
    Print(HNotification, "Get Event");
    return std::shared_ptr<hanalysis::HEvent>(new HEvent());
}
