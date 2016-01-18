/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca
{

class Names
{
public:
    Names();
    Names(std::string const& name);
    Names(std::string const& name, std::string const& latex_name);
    std::string const& Name()const;
    std::string const& LatexName()const;
    void SetName(std::string const& name);
    void SetLatexName(std::string const& latex_name);
    void Set(std::string const& name, std::string const& latex_name);
private:
    std::string name_;
    std::string latex_name_;
};

}
