/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Names.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{

Names::Names()
{
    INFO0;
}

Names::Names(std::string const& name)
{
    INFO0;
    name_ = name;
}

Names::Names(std::string const& name, Latex const& latex_name)
{
    INFO0;
    Set(name, latex_name);
}

std::string Names::Name() const
{
    INFO(name_);
    return name_;
}

Latex Names::LatexName() const
{
    INFO0;
    return latex_name_.empty() ? name_ : latex_name_;
}

void Names::SetName(std::string const& name)
{
    INFO0;
    name_ = name;
}

void Names::SetLatexName(Latex const& latex_name)
{
    INFO0;
    latex_name_ = latex_name;
}

void Names::Set(const std::string& name, const Latex& latex_name)
{
    INFO0;
    latex_name_ = latex_name;
    name_ = name;
}

void Names::Set(const std::string& name)
{
    INFO0;
    latex_name_ = name;
    name_ = name;
}


}
