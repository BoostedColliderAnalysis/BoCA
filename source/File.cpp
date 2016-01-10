/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TFile.h"
#include "TTree.h"

#include "Types.hh"
#include "File.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

File::File(std::vector<std::string> const& processes, std::string const& base_path, std::string const& file_suffix, std::string const& nice_name, boca::Crosssection crosssection, boca::Mass mass)
{
    Info0;
    SetVariables();
    process_folders_ = processes;
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    crosssection_ = crosssection;
    names_.SetLatexName(nice_name);
    mass_ = mass;
}

std::string File::FileSuffix() const
{
    Info0;
    switch (Source()) {
    case boca::Source::delphes :
        return "_delphes_events.root";
    case boca::Source::parton :
        return "_unweighted_events.root";
    case boca::Source::pgs :
        return "_pgs_events.root";
    default :
        Error("file suffix", "no source");
        return "";
    }
}

std::string File::TreeName() const
{
    Info0;
    switch (Source()) {
    case boca::Source::delphes :
        return "Delphes";
    case boca::Source::parton :
        return "LHEF";
    case boca::Source::pgs :
        return "LHCO";
    default :
        Error("tree name", "no tree name");
        return "";
    }
}

std::string File::Title() const
{
    Info0;
    return process_folders_.front() + "-" + run_folder_;
}

std::string File::MadGraphFilePath() const
{
    Info0;
    return base_path_ + process_folders_.front() + "/events/" + run_folder_ + "/";
}

void File::SetVariables()
{
    Info0;
    run_folder_ = "run_01";
    tag_name_ = "tag_1";
}

std::vector<std::string> File::Paths() const
{
    Info0;
    std::vector<std::string> FilePaths;
    for (auto const & process_folder : process_folders_) FilePaths.emplace_back(base_path_ + process_folder + file_suffix_);
    return FilePaths;
}

// boca::TreeReader File::TreeReader()
// {
//     Info0;
//     for (auto const & path : Paths()) Note(path);
//     Error(Paths().front());
//     return {Paths(), tree_name()};
// }

boca::Crosssection File::Crosssection() const
{
    Info0;
    return crosssection_;
}

boca::Crosssection File::CrosssectionError() const
{
    Info0;
    return crosssection_error_;
}

boca::Mass File::Mass() const
{
    Info0;
    return mass_;
}

boca::Source File::Source() const
{
    Info0;
    return source_;
}

// std::string File::LatexName() const
// {
//     Info0;
//     return names_.LatexName();
// }
std::string File::Name() const
{
    return names_.Name();
}

Names File::Names() const
{
    return names_;
}


}
