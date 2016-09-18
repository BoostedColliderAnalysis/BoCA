/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TFile.h"
#include "TTree.h"

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/File.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

// File::File(std::vector<std::string> const& file_names) :
//     file_names_(file_names)
// {}
//
// File::File(std::vector<std::string> const& file_names, boca::Names const &names) :
//     file_names_(file_names) ,
//     names_(names)
// {}
//
// File::File(std::vector<std::string> const& file_names, boca::Names const &names, boca::Crosssection crosssection) :
//     file_names_(file_names) ,
//     names_(names),
//     crosssection_(crosssection)
// {}

// File::File(std::vector<std::string> const& file_names, boca::Names const &names, Number<boca::Crosssection> crosssection) :
//     file_names_(file_names) ,
//     names_(names),
//     crosssection_(crosssection)
// {}

File::File(std::vector<std::string> const& file_names, boca::Names const &names, Number<boca::Crosssection> crosssection,  boca::Mass const& mass) :
    file_names_(file_names) ,
    names_(names),
    crosssection_(crosssection),
    mass_(mass)
{}

File::File(std::vector<std::string> const &file_names, std::string const &base_path, std::string const &file_suffix, latex::String const &latex_name, boca::Crosssection const &crosssection, boca::Mass const &mass)
{
    INFO0;
    file_names_ = file_names;
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    crosssection_.Value() = crosssection;
    names_.Set(latex_name.str(latex::Medium::latex), latex_name); // FIXME dont do that
    mass_ = mass;
}

File::File(std::vector<std::string> const &file_names, std::string const &base_path, std::string const &file_suffix, boca::Names const &latex_name, boca::Crosssection const &crosssection, boca::Mass const &mass)
{
    INFO0;
    file_names_ = file_names;
    base_path_ = base_path;
    file_suffix_ = file_suffix;
    crosssection_.Value() = crosssection;
    names_ = latex_name;
    mass_ = mass;
}

std::string File::FileSuffix() const
{
    INFO0;
    switch (Source()) {
    case boca::Source::delphes :
        return "_delphes_events.root";
    case boca::Source::parton :
        return "_unweighted_events.root";
    case boca::Source::pgs :
        return "_pgs_events.root";
        DEFAULT(boca::Name(Source()), "");
    }
}

std::string File::TreeName() const
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

std::string File::Title() const
{
    INFO0;
    return file_names_.front() + "-" + RunFolder();
}

std::string File::TagName() const
{
    INFO0;
    return "tag_1";
}

std::string File::RunFolder() const
{
    INFO0;
    return "run_01";
}

std::vector<std::string> File::Paths() const
{
    INFO0;
    return Transform(file_names_, [&](std::string const & process_folder) {
        return base_path_ + process_folder + file_suffix_;
    });
}

boca::Crosssection File::Crosssection() const
{
    INFO0;
    return crosssection_.Value();
}

boca::Crosssection File::CrosssectionError() const
{
    INFO0;
    return crosssection_.Error();
}

boca::Mass File::Mass() const
{
    INFO0;
    return mass_;
}

boca::Source File::Source() const
{
    INFO0;
    return source_;
}

std::string File::Name() const
{
    return names_.Name();
}

Names File::Names() const
{
    return names_;
}



std::string File::RelativePath()
{
    return relative_path_;
}

}
