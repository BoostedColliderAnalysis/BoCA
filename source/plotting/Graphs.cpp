/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/algorithm_ext/erase.hpp>

#include "TAxis.h"

#include "plotting/Style.hh"
#include "plotting/Graphs.hh"
// #define INFORMATION
#include "generic/DEBUG.hh"

namespace boca
{

Graphs::Graphs(std::string const& path, std::string const& name, bool show_title):
    Canvas(path, name, show_title)
{
    INFO0;
    if (show_title) multi_graph_.SetTitle(Title().c_str());
}

Graphs::~Graphs()
{
    INFO0;
    Draw();
    SaveAs(FileName());
}

void Graphs::AddGraph(std::vector<double> const& xs, std::vector<double> const& ys, std::string const& name)
{
    INFO(xs.size(), ys.size(), name);
    CHECK(xs.size() == ys.size() && !xs.empty(), xs.size(), ys.size());
    std::vector<double> xs2 = xs;
    range_.WidenX(MinMax(boost::remove_erase(xs2, 0)));
    std::vector<double> ys2 = ys;
    range_.WidenY(MinMax(boost::remove_erase(ys2, 0)));
    TGraph graph(xs.size(), xs.data(), ys.data());
    SetLine(graph, graphs_.size());
    graph.SetTitle(name.c_str());
    graphs_.emplace_back(graph);
    datas_.emplace_back(std::make_pair(xs, ys));
}

void Graphs::SetLegend(boca::Orientation orientation, std::string const& title)
{
    INFO(title, Name(orientation));
    AddGraphs();
    for (auto & line : lines_) if (!line.second.empty()) legend_.AddEntry(line.first, line.second);
    legend_.SetOrientation(orientation, title);
}

void Graphs::Draw()
{
    INFO0;
    multi_graph_.Draw("al");
    for (auto & line : lines_) {
      line.first.SetY1(RangeY().Min());
      line.first.SetY2(RangeY().Max());
      line.first.Draw();
    }
    legend_.Draw();
}

void Graphs::SetXAxis(std::string const& title, boca::Range<double> const& range)
{
    INFO(title);
    if (range) {
        range_.SetX(range);
        range_.ResetY();
        for (auto const & data : datas_) range_.WidenY(range, data.first, data.second);
    }
    AddGraphs();
    if (!multi_graph_.GetXaxis()) return;
    INFO("set title", range_.Horizontal().Floor(), range_.Horizontal().Ceil());
    SetAxis(*multi_graph_.GetXaxis(), title);
    multi_graph_.GetXaxis()->SetLimits(range_.Horizontal().Floor(), range_.Horizontal().Ceil());
}

void Graphs::SetYAxis(std::string const& title, boca::Range<double> const& range)
{
    INFO(title);
    range_.WidenY(range);
//     if (range) {
//         range_.SetY(range);
//         range_.ResetX();
//         for (auto const & graph : graphs_) {
//             std::vector<double> xs(graph.GetX(), graph.GetX() + graph.GetMaxSize());
//             std::vector<double> ys(graph.GetY(), graph.GetY() + graph.GetMaxSize());
//             range_.WidenX(range, xs, ys);
//         }
//     }
    AddGraphs();
    if (!multi_graph_.GetYaxis()) return;
    INFO("set title", range_.Vertical().Floor(), range_.Vertical().Ceil());
    SetAxis(*multi_graph_.GetYaxis(), title);
    multi_graph_.GetYaxis()->SetLimits(range_.Vertical().Floor(), range_.Vertical().Ceil());
    multi_graph_.SetMinimum(range_.Vertical().Floor());
    multi_graph_.SetMaximum(range_.Vertical().Ceil());
    SetLog(range_.Vertical());
}

Range<double> Graphs::RangeY()
{
    INFO0;
    if (!multi_graph_.GetYaxis()) return {};
    return {multi_graph_.GetYaxis()->GetXmin(), multi_graph_.GetYaxis()->GetXmax()};
}

Range<double> Graphs::RangeX()
{
    INFO0;
    if (!multi_graph_.GetXaxis()) return {};
    return {multi_graph_.GetXaxis()->GetXmin(), multi_graph_.GetXaxis()->GetXmax()};
}

void Graphs::AddGraphs()
{
    INFO0;
    Draw();
    if (multi_graph_.GetListOfGraphs()) return;
    for (auto & graph : graphs_) {
        multi_graph_.Add(&graph);
        if (graphs_.size() > 1) legend_.AddEntry(graph, graph.GetTitle());
    }
}

void Graphs::AddLine(double x_value, std::string const& title)
{
    INFO(x_value);
//     if (!RangeX().Inside(x_value)) return;
    if (x_value <= -1 ) return; // FIXME reenable proper check
    Range<double> y = RangeY();
    TLine line(x_value, y.Min(), x_value, y.Max());
    SetLine(line, graphs_.size() + lines_.size());
    lines_.emplace_back(std::make_pair(line, title));
}

}
