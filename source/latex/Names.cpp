/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/latex/Names.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

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

Names::Names(latex::String const& latex_name)
{
    INFO0;
    Set(latex_name.str(latex::Medium::plain), latex_name);
}

Names::Names(std::string const& name, latex::String const& latex_name)
{
    INFO0;
    Set(name, latex_name);
}

std::string Names::Name() const
{
    INFO(name_);
    return name_;
}

latex::String Names::LatexName() const
{
    INFO(latex_name_.empty(), latex_name_.str(latex::Medium::latex), latex_name_.str(latex::Medium::plain));
    return latex_name_.empty() ? name_ : latex_name_;
}

std::string Names::Plain() const
{
    INFO(name_);
    return name_;
}

latex::String Names::Latex() const
{
    INFO(latex_name_.empty(), latex_name_.str(latex::Medium::latex), latex_name_.str(latex::Medium::plain));
    return latex_name_.empty() ? name_ : latex_name_;
}

void Names::SetName(std::string const& name)
{
    INFO0;
    name_ = name;
}

void Names::SetLatexName(latex::String const& latex_name)
{
    INFO0;
    latex_name_ = latex_name;
}

void Names::Set(const std::string& name, const latex::String& latex_name)
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
