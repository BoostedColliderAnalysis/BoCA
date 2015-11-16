/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TFile.h"
#include "TTree.h"

#include "Types.hh"
#include "File.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

File::File(Strings const& processes, std::string const& base_path, std::string const& file_suffix, std::string const& nice_name, Crosssection crosssection, Mass mass)
{
    Info0;
    SetVariables();
    process_folders_ = processes;
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    crosssection_ = crosssection;
    nice_name_ = nice_name;
    mass_ = mass;
}

std::string File::file_suffix() const
{
    Info0;
    switch (source()) {
    case Source::delphes :
        return "_delphes_events.root";
    case Source::parton :
        return "_unweighted_events.root";
    case Source::pgs :
        return "_pgs_events.root";
    default :
        Error("file suffix", "no source");
        return "";
    }
}

std::string File::tree_name() const
{
    Info0;
    switch (source()) {
    case Source::delphes :
        return "Delphes";
    case Source::parton :
        return "LHEF";
    case Source::pgs :
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

Strings File::Paths() const
{
    Info0;
    Strings FilePaths;
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

Crosssection File::crosssection() const
{
    Info0;
    return crosssection_;
}

Crosssection File::crosssection_error() const
{
    Info0;
    return crosssection_error_;
}

Mass File::mass() const
{
    Info0;
    return mass_;
}

Source File::source() const
{
    Info0;
    return source_;
}

std::string File::nice_name() const
{
    Info0;
    return nice_name_;
}


}
