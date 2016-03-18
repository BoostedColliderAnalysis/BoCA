/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Names.hh"
// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

Names::Names() {}

Names::Names(std::string const& name)
{
    name_ = name;
}

Names::Names(std::string const& name, std::string const& latex_name)
{
    Set(name, latex_name);
}

std::string const& Names::Name() const
{
    INFO0;
    return name_;
}

std::string const& Names::LatexName() const
{
    INFO0;
    return latex_name_.empty() ? name_ : latex_name_;
}

void Names::SetName(std::string const& name)
{
    INFO0;
    name_ = name;
}

void Names::SetLatexName(std::string const& latex_name)
{
    INFO0;
    latex_name_ = latex_name;
}

void Names::Set(const std::string& name, const std::string& latex_name)
{
    latex_name_ = latex_name;
    name_ = name;
}

void Names::Set(const std::string& name)
{
  latex_name_ = name;
  name_ = name;
}


}
