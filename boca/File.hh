/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Names.hh"
#include "boca/physics/Units.hh"
#include "boca/io/TreeReader.hh"

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

    File(const std::vector< std::string >& processes, const std::string& base_path, const std::string& file_suffix, Latex const& latex_name, const boca::Crosssection& crosssection = pb, const boca::Mass& mass = 0_eV);

    File(const std::vector< std::string >& processes, const std::string& base_path, const std::string& file_suffix, const boca::Names& nice_name, const boca::Crosssection& crosssection = pb, const boca::Mass& mass = 0_eV);

    std::string Title() const;

    boca::Crosssection Crosssection() const;

    boca::Crosssection CrosssectionError() const;

    boca::Mass Mass() const;

    boca::Source Source() const;

    std::string TreeName() const;

    Latex LatexName() const;

    std::string Name() const;

    boca::Names Names()const;

    std::vector<std::string> Paths() const;

protected:

    std::string MadGraphFilePath() const;

private:

    std::string TagName() const;

    std::string RunFolder() const;

    std::string FileSuffix() const;

    std::string BasePath(){
      return base_path_;
//       return "$HOME/Development/MadGraph/";
//       return @MadGraphPath@;
    }

    std::vector<std::string> process_folders_;

    boca::Crosssection crosssection_ = pb;

    boca::Crosssection crosssection_error_ = 0_b;

    boca::Mass mass_ = massless;

    std::string file_suffix_ = ".root";

    std::string base_path_ = "$HOME/Development/MadGraph/";

    boca::Names names_;

    boca::Source source_ = boca::Source::delphes;

};

}
