/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Latex.hh"

namespace boca
{

class Names
{
public:
    Names();
    Names(std::string const& name);
    Names(std::string const& name, Latex const& latex_name);
    std::string Name()const;
    Latex LatexName()const;
    void SetName(std::string const& name);
    void SetLatexName(Latex const& latex_name);
    void Set(std::string const& name, Latex const& latex_name);
    void Set(std::string const& name);
private:
    std::string name_;
    Latex latex_name_;
};

}
