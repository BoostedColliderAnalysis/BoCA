/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/lexical_cast.hpp>

#include "boca/latex/File.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

  namespace latex
  {

File::File(std::string const& name) : environment_("document")
{
    latex_file_.open(name + ".tex");
    latex_file_ << Article("a4paper", "11pt")
                << UsePackage("booktabs")
                << UsePackage("graphicx")
                << UsePackage("amsmath")
                << UsePackage("fullpage", Optional("cm"))
                << UsePackage("units")
                << UsePackage("color")
                << SetCounter("topnumber", 0)
                << SetCounter("bottomnumber", 6)
                << SetCounter("totalnumber", 6)
                << RenewCommand("bottomfraction", 1)
                << RenewCommand("textfraction", 0)
                << environment_.Begin();
}

File::~File()
{
    latex_file_ << environment_.End();
    latex_file_.close();
}

void File::operator<<(std::string const& string)
{
    latex_file_ << string;
}

void File::AddTable(Table const& table)
{
    latex_file_ << table.str();
}

void File::AddGraphic(Graphic const& graphic)
{
    latex_file_ << graphic.str();
}

void File::AddTitle(boca::Mass const& mass)
{
    INFO0;
    if (mass == massless) return;
    auto mass_string = std::stringstream{};
    mass_string << boost::units::engineering_prefix << "Mass = " << mass;
    latex_file_ << "\n" << Command("section*", mass_string.str());

}

}

}
