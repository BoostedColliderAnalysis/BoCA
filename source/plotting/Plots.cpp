/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "plotting/Plots.hh"

// #define DEBUG
#include "Debug.hh"

namespace boca
{

void Plots::SetNames(NamePairs const& names, NamePairs const& latex_names)
{
    Info0;
    for (auto & plot : plots_) {
        int index = &plot - &plots_.front();
        plot.XAxis().SetName(names.at(index).first);
        plot.XAxis().SetLatexName(latex_names.at(index).first);
        plot.YAxis().SetName(names.at(index).second);
        plot.YAxis().SetLatexName(latex_names.at(index).second);
        plot.Title().SetName(name_);
        plot.Title().SetLatexName(info_branch_.Name);
    }
}

Plots::Plots(const InfoBranch& info_branch)
{
    Info0;
    info_branch_ = info_branch;
}

std::vector<Plot> const& Plots::plots() const
{
    Info0;
    return plots_;
}

std::vector<Plot> & Plots::plots()
{
    Info0;
    return plots_;
}

void Plots::SetName(std::string const& name)
{
    Info0;
    name_ = name;
}

}
