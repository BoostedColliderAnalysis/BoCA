/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Names.hh"
#include "boca/physics/Units.hh"
#include "boca/physics/Number.hh"
#include "boca/io/TreeReader.hh"

namespace boca
{

using namespace std::string_literals;

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class File
{

public:

//     File(std::vector<std::string> const& file_names);
//
//     File(std::vector<std::string> const& file_names, boca::Names const& names);
//
//     File(std::vector<std::string> const& file_names, boca::Names const& names, boca::Crosssection crosssection);
//
//     File(std::vector<std::string> const& file_names, boca::Names const& names, Number<boca::Crosssection> crosssection);

    File(std::vector<std::string> const& file_names = {}, boca::Names const& names = ""s, Number<boca::Crosssection> crosssection = 0_pb,  boca::Mass const& mass = 0_eV);

    File(std::vector<std::string> const& file_names, const std::string& base_path, const std::string& file_suffix, latex::String const& latex_name, const boca::Crosssection& crosssection = pb, boca::Mass const& mass = 0_eV);

    File(std::vector<std::string> const& file_names, const std::string& base_path, const std::string& file_suffix, const boca::Names& nice_name, const boca::Crosssection& crosssection = pb, boca::Mass const& mass = 0_eV);

    std::string Title() const;

    boca::Crosssection Crosssection() const;

    boca::Crosssection CrosssectionError() const;

    boca::Mass Mass() const;

    boca::Source Source() const;

    std::string TreeName() const;

    latex::String LatexName() const;

    std::string Name() const;

    boca::Names Names() const;

    std::vector<std::string> Paths() const;

    std::string RelativePath();

    void SetPath(std::string const& path) {
        base_path_ = path;
    }

    void SetSuffix(std::string const& suffix) {
        file_suffix_ = suffix;
    }

private:

    std::string TagName() const;

    std::string RunFolder() const;

    std::string FileSuffix() const;

    std::string BasePath(){
      return base_path_;
//       return "$HOME/Development/MadGraph/";
//       return @MadGraphPath@;
    }

    std::vector<std::string> file_names_;

    boca::Names names_;

    Number<boca::Crosssection> crosssection_;

    boca::Mass mass_ = massless;

    std::string file_suffix_ = ".root";

    std::string base_path_ = "$HOME/Development/MadGraph/";

    std::string relative_path_;

    boca::Source source_ = boca::Source::delphes;

};

}
