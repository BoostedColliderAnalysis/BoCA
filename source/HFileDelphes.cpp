# include "HFileDelphes.hh"

hanalysis::hdelphes::HFile::HFile()
{
    Print(HInformation, "Constructor");
//     SetVariables();
    tree_name_ = "Delphes";
    file_suffix_ = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
    tree_name_ = "Delphes";
    file_suffix_ = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
//     RunFolder = Run;
    tree_name_ = "Delphes";
    file_suffix_ = "_delphes_events.root";
}

Strings hanalysis::hdelphes::HFile::Paths() const
{
    Print(HInformation, "FilePath");
    Strings FilePahts;
    FilePahts.emplace_back(GetMadGraphFilePath() + tag_name_ +  file_suffix_);
    return FilePahts;
}
