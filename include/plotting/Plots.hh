/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "plotting/Plot.hh"
#include "Branches.hh"

namespace boca
{

using NamePairs = std::vector<std::pair<Names, Names>>;

class Plots
{
public:
    Plots(InfoBranch const& info_branch);
    void SetNames(NamePairs const& names);
    std::vector<Plot> const& plots() const;
    std::vector<Plot>& plots();
    void SetName(std::string const& name);
private:
    std::vector<Plot> plots_;
    InfoBranch info_branch_;
    std::string name_;
};

}
