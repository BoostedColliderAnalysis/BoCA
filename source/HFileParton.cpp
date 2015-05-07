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

std::string hanalysis::hparton::HFile::tree_name() const
{
    Print(HInformation, "Get Tree String");
    tree_name_ = "LHEF";
    return tree_name_;
}

Strings hanalysis::hparton::HFile::Paths() const
{
    Print(HInformation, "FilePath");
    file_suffix_ = "_unweighted_events.root";
    Strings FilePaths;
    FilePaths.emplace_back(GetMadGraphFilePath() + tag_name_ +  file_suffix_);
    return FilePaths;
}

// std::shared_ptr<hanalysis::HEvent> hanalysis::hparton::HFile::Event()
// {
//     Print(HNotification, "Get Event");
//     return std::shared_ptr<hanalysis::HEvent>(new HEvent());
// }
