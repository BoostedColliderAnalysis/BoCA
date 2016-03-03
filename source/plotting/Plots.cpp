/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Plots.hh"

// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

Plots::Plots() {}

Plots::Plots(boca::InfoBranch const& info_branch)
{
    INFO0;
    info_branch_ = info_branch;
}

void Plots::SetNames(NamePairs const& names)
{
    INFO0;
    for (auto & plot : plots_) {
        int index = &plot - &plots_.front();
        plot.XAxis() = names.at(index).first;
        plot.YAxis() = names.at(index).second;
        plot.Title() = info_branch_.Names();
    }
}

void Plots::SetNames(std::vector<boca::Names> const& names)
{
    INFO0;
    for (auto & plot : plots_) {
        int index = &plot - &plots_.front();
        plot.XAxis() = names.at(index);
        plot.Title() = info_branch_.Names();
    }
}

std::vector<Plot> const& Plots::PlotVector() const
{
    INFO0;
    return plots_;
}

std::vector<Plot>& Plots::PlotVector()
{
    INFO0;
    return plots_;
}

boca::Range< float > Plots::XRange() const
{
    Range<float> range;
    for (auto const & plot : plots_) range.Widen(plot.XRange());
    return range;
}
Names& Plots::Names()
{
    return names_;
}
Names const& Plots::Names() const
{
  return names_;
}
boca::InfoBranch const& Plots::InfoBranch() const
{
    return info_branch_;
}

}
