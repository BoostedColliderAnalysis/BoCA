# include "HFileParton.hh"

hanalysis::hparton::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
}

hanalysis::hparton::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
}

hanalysis::hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
//     RunFolder = Run;
}

std::string hanalysis::hparton::HFile::TreeName() const
{
    Print(HInformation, "Get Tree String");
    TreeNameM = "LHEF";
    return TreeNameM;
}

Strings hanalysis::hparton::HFile::Paths() const
{
    Print(HInformation, "FilePath");
    FileSuffix = "_unweighted_events.root";
    Strings FilePaths;
    FilePaths.emplace_back(GetMadGraphFilePath() + TagName +  FileSuffix);
    return FilePaths;
}

// std::shared_ptr<hanalysis::HEvent> hanalysis::hparton::HFile::Event()
// {
//     Print(HNotification, "Get Event");
//     return std::shared_ptr<hanalysis::HEvent>(new HEvent());
// }
