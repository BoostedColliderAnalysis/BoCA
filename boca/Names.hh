/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/latex/String.hh"

namespace boca
{

class Names
{
public:
    Names();
    Names(std::string const& name);
    Names(std::string const& name, latex::String const& latex_name);
    std::string Name()const;
    latex::String LatexName()const;
    void SetName(std::string const& name);
    void SetLatexName(latex::String const& latex_name);
    void Set(std::string const& name, latex::String const& latex_name);
    void Set(std::string const& name);
private:
    std::string name_;
    latex::String latex_name_;
};

}
