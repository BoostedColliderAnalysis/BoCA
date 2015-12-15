/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "plotting/Plot.hh"
#include "Branches.hh"

namespace boca
{

typedef std::vector<std::pair<std::string, std::string>> NamePairs;

class Plots
{
public:
    Plots(InfoBranch const& info_branch);
    void SetNames(NamePairs const& names, NamePairs const& latex_names);
    std::vector<Plot> const& plots() const;
    std::vector<Plot>& plots();
    void SetName(std::string const& name);
private:
    std::vector<Plot> plots_;
    InfoBranch info_branch_;
    std::string name_;
};

}
