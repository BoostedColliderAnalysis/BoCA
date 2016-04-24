/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/plotting/Plots.hh"

#include "boca/generic/Vector.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

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
        auto index = Position(plots_, plot);
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
  INFO0;
    Range<double> range;
    for (auto const & plot : plots_) range.Widen(plot.XRange());
    return range;
}
Names& Plots::Names()
{
  INFO0;
    return names_;
}
Names const& Plots::Names() const
{
  INFO0;
    return names_;
}
boca::InfoBranch const& Plots::InfoBranch() const
{
  INFO0;
    return info_branch_;
}

}
