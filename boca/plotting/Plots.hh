/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/plotting/Plot.hh"
#include "boca/Branches.hh"

namespace boca
{

using NamePairs = std::vector<std::pair<Names, Names>>;

class Plots
{
public:
    Plots();
    Plots(boca::InfoBranch const& info_branch);
    void SetNames(NamePairs const& names);
    void SetNames(const std::vector< boca::Names >& names);
    std::vector<Plot> const& PlotVector() const;
    std::vector<Plot>& PlotVector();
//     void SetName(std::string const& name);
    boca::Names & Names();
    boca::Names const& Names() const;
    Range<double> XRange() const;
    boca::InfoBranch const& InfoBranch()const;
private:
    std::vector<Plot> plots_;
    boca:: InfoBranch info_branch_;
    boca::Names names_;
};

}
