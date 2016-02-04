/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Plots.hh"

// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

void Plots::SetNames(NamePairs const& names)
{
    INFO0;
    for (auto & plot : plots_) {
        int index = &plot - &plots_.front();
        plot.XAxis() = names.at(index).first;
//         plot.XAxis().SetLatexName(names.at(index).first.LatexName());
        plot.YAxis() = names.at(index).second;
//         plot.YAxis().SetLatexName(names.at(index).second.LatexName());
        plot.Title() = info_branch_.Names();
//         plot.Title().SetLatexName(info_branch_.LatexName());
    }
}

Plots::Plots(const InfoBranch& info_branch)
{
    INFO0;
    info_branch_ = info_branch;
}

std::vector<Plot> const& Plots::plots() const
{
    INFO0;
    return plots_;
}

std::vector<Plot> & Plots::plots()
{
    INFO0;
    return plots_;
}

void Plots::SetName(std::string const& name)
{
    INFO0;
    name_ = name;
}

}
