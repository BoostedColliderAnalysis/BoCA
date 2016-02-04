/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Names.hh"
#include "physics/Units.hh"
#include "TreeReader.hh"

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

    File(std::vector<std::string> const& processes, std::string const& run_folder, std::string const& file_suffix, std::string const& nice_name = "", boca::Crosssection crosssection = pb, boca::Mass mass = massless);

    std::string Title() const;

    boca::Crosssection Crosssection() const;

    boca::Crosssection CrosssectionERROR() const;

    boca::Mass Mass() const;

    boca::Source Source() const;

    std::string TreeName() const;

    std::string LatexName() const;

    std::string Name() const;

    boca::Names Names()const;

    std::vector<std::string> Paths() const;

protected:

    void  SetVariables();

    std::string MadGraphFilePath() const;

private:

    std::string FileSuffix() const;

    std::string base_path_ = "$HOME/Development/MadGraph/";

    std::vector<std::string> process_folders_;

    std::string run_folder_;

    std::string tag_name_;

    std::string tree_name_;

    boca::Crosssection crosssection_ = pb;

    boca::Crosssection crosssection_error_ = 0;

    boca::Mass mass_ = massless;

    std::string file_suffix_ = ".root";

    boca::Names names_;

    boca::Source source_ = boca::Source::delphes;

};

}
