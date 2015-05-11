# include "HFileParton.hh"

hanalysis::hparton::HFile::HFile()
{
    Print(kInformation, "Constructor");
    SetVariables();
}

hanalysis::hparton::HFile::HFile(const std::string &Process)
{
    Print(kInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
}

hanalysis::hparton::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(kInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
//     RunFolder = Run;
}

std::string hanalysis::hparton::HFile::tree_name() const
{
    Print(kInformation, "Get Tree String");
    tree_name_ = "LHEF";
    return tree_name_;
}

Strings hanalysis::hparton::HFile::Paths() const
{
    Print(kInformation, "FilePath");
    file_suffix_ = "_unweighted_events.root";
    Strings FilePaths;
    FilePaths.emplace_back(GetMadGraphFilePath() + tag_name_ +  file_suffix_);
    return FilePaths;
}

// std::shared_ptr<hanalysis::HEvent> hanalysis::hparton::HFile::Event()
// {
//     Print(kNotification, "Get Event");
//     return std::shared_ptr<hanalysis::HEvent>(new HEvent());
// }
