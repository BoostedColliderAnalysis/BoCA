/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TFile.h"
#include "TTree.h"

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/io/FileInfo.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

FileInfo::FileInfo(std::vector<std::string> const &file_names, boca::Names const &names, Number<boca::Crosssection> crosssection,  boca::Mass const &mass) :
    file_names_(file_names) ,
    names_(names),
    crosssection_(crosssection),
    mass_(mass)
{}

Names FileInfo::Names() const
{
    return names_;
}

Number<boca::Crosssection> FileInfo::Crosssection() const
{
    INFO0;
    return crosssection_;
}

boca::Mass FileInfo::Mass() const
{
    INFO0;
    return mass_;
}

std::string FileInfo::GeneratorTreeName() const
{
    INFO0;
    switch (Source()) {
    case boca::Source::delphes :
        return "Delphes";
    case boca::Source::parton :
        return "LHEF";
    case boca::Source::pgs :
        return "LHCO";
        DEFAULT(boca::Name(Source()), "");
    }
}

boca::Source FileInfo::Source() const
{
    INFO0;
    return source_;
}

std::string FileInfo::TaggerTreeName() const
{
    INFO0;
    return FileNames().front()/* + "-" + RunFolder()*/;
}

std::vector<std::string> FileInfo::Paths() const
{
    INFO0;
    return Transform(FileNames(), [&](std::string const & file_name) {
        return Path() + file_name + FileSuffix();
    });
}

std::string FileInfo::Path() const
{
    return path_;
}

std::string FileInfo::FileSuffix() const
{
    INFO0;
    return ".root";
}

void FileInfo::SetPath(const std::string &path)
{
    path_ = path;
}

std::vector<std::string> FileInfo::FileNames() const
{
    return file_names_;
}


void FileInfo::SetSource(const boca::Source &source)
{
    source_ = source;
}

}
