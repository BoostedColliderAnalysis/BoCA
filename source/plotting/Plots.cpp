/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Plots.hh"

#include "Vector.hh"
// #define DEBUGGING
#include "DEBUG.hh"

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
        int index = Position(plots_, plot);
        plot.XAxis() = names.at(index).first;
        plot.YAxis() = names.at(index).second;
        plot.Title() = info_branch_.Names();
    }
}

void Plots::SetNames(std::vector<boca::Names> const& names)
{
    INFO0;
    for (auto & plot : plots_) {
        plot.XAxis() = names.at(Position(plots_, plot));
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

boca::Range< double > Plots::XRange() const
{
    Range<double> range;
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
