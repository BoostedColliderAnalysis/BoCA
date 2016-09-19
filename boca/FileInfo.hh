/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Units.hh"
#include "boca/physics/Number.hh"
#include "boca/io/Souce.hh"
#include "boca/Names.hh"

namespace boca
{

using namespace std::string_literals;

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class FileInfo
{

public:

    FileInfo(std::vector<std::string> const& file_names = {}, boca::Names const& names = ""s, Number<boca::Crosssection> crosssection = 0_pb,  boca::Mass const& mass = 0_eV);

    void SetPath(std::string const& path);

    void SetSource(boca::Source const& source);

    boca::Names Names() const;

    Number<boca::Crosssection> Crosssection() const;

    boca::Mass Mass() const;

    std::string TaggerTreeName() const;

    std::string GeneratorTreeName() const;

    std::vector<std::string> Paths() const;

private:

    std::vector<std::string> FileNames() const;

    latex::String LatexName() const;

    std::string FileSuffix() const;

    std::string Path() const;

    boca::Source Source() const;

    std::vector<std::string> file_names_;

    boca::Names names_;

    Number<boca::Crosssection> crosssection_;

    boca::Mass mass_ = massless;

    std::string path_ = "./";

    boca::Source source_ = boca::Source::delphes;

};

}
