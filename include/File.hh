/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Event.hh"
// #include "TreeReader.hh"

namespace boca
{

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class File
{

public:

    File(Strings const& processes, std::string const& run_folder, std::string const& file_suffix, std::string const& nice_name = "", Crosssection crosssection = pb, Mass mass = massless);

//     boca::TreeReader TreeReader();

    std::string Title() const;

    Crosssection crosssection() const;

    std::string file_suffix() const;

    Crosssection crosssection_error() const;

    Mass mass() const;
    Source source() const;

    std::string tree_name() const;

    std::string nice_name() const;

    Strings Paths() const;

protected:

    void  SetVariables();

    std::string MadGraphFilePath() const;

private:

    std::string base_path_ = "$HOME/Development/MadGraph/";

    Strings process_folders_;

    std::string run_folder_;

    std::string tag_name_;

    std::string tree_name_;

    Crosssection crosssection_ = pb;

    Crosssection crosssection_error_ = 0;

    Mass mass_ = massless;

    std::string file_suffix_ = ".root";

    std::string nice_name_;

    Source source_ = Source::delphes;

};

}
