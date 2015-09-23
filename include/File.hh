/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include  "exroot/ExRootAnalysis.hh"
#include "ClonesArrays.hh"
#include "Event.hh"
#include "Units.hh"

namespace boca
{

typedef std::vector<std::string> Strings;

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

    /**
     * @brief destructor
     *
     */
    virtual ~File();

    exroot::TreeReader TreeReader();

    ClonesArrays clones_arrays();

    Event event();

    /**
     * @brief Name of Process
     *
     */
    std::string Title() const;

    Crosssection crosssection() const {
        return crosssection_;
    }

    std::string file_suffix() const;

    Crosssection crosssection_error() const {
        return crosssection_error_;
    }

    Mass mass() const {
        return mass_;
    }
    Source source() const {
        return source_;
    }

    std::string tree_name() const;

    std::string nice_name() const {
        return nice_name_;
    }

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

    TChain* chain_ = nullptr;
};

}
