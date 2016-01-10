/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Names.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

std::string const& Names::Name() const
{
    Info0;
    return name_;
}

std::string const& Names::LatexName() const
{
    Info0;
    return latex_name_;
}

void Names::SetName(std::string const& name)
{
    Info0;
    name_ = name;
}

void Names::SetLatexName(std::string const& latex_name)
{
    Info0;
    latex_name_ = latex_name;
}

}
