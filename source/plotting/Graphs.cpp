/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm_ext/erase.hpp>

#include "TAxis.h"

#include "plotting/Style.hh"
#include "plotting/Graphs.hh"
#define INFORMATION
#include "Debug.hh"

namespace boca
{

Graphs::Graphs(std::string const& path, std::string const& name, bool show_title):
    Canvas(path, name, show_title)
{
    Info0;
    if (show_title) multi_graph_.SetTitle(Title().c_str());
}

Graphs::~Graphs()
{
    Info0;
    Draw();
    SaveAs(FileName());
}

void Graphs::AddGraph(std::vector<float> const& xs, std::vector<float> const& ys, std::string const& name)
{
    INFO(xs.size(), ys.size(), name);
    Check(xs.size() == ys.size() && xs.size() > 0, xs.size(), ys.size());
    std::vector<float> xs2 = xs;
    bounds_.WidenX(MinMax(boost::remove_erase(xs2, 0)));
    std::vector<float> ys2 = ys;
    bounds_.WidenY(MinMax(boost::remove_erase(ys2, 0)));
    TGraph graph(xs.size(), &xs.front(), &ys.front());
    SetLine(graph, graphs_.size());
    graph.SetTitle(name.c_str());
    graphs_.emplace_back(graph);
    datas_.emplace_back(std::make_pair(xs, ys));
}

void Graphs::SetLegend(boca::Orientation orientation, std::string const& title)
{
    INFO(title);
    AddGraphs();
    legend_.SetOrientation(orientation, title);
}

void Graphs::Draw()
{
    Info0;
    multi_graph_.Draw("al");
    if (graphs_.size() > 1) legend_.Draw();
    for (auto & line : lines_) line.Draw();
}

void Graphs::SetXAxis(std::string const& title, boca::Bounds<float> const& bounds)
{
    INFO(title);
    if (bounds) {
        bounds_.SetX(bounds);
        bounds_.ResetY();
        for (auto const & data : datas_) bounds_.WidenY(bounds, data.first, data.second);
    }
    AddGraphs();
    if (!multi_graph_.GetXaxis()) return;
    INFO("set title",bounds_.Horizontal().Floor(), bounds_.Horizontal().Ceil());
    SetTitle(*multi_graph_.GetXaxis(), title);
    multi_graph_.GetXaxis()->SetLimits(bounds_.Horizontal().Floor(), bounds_.Horizontal().Ceil());
}

void Graphs::SetYAxis(std::string const& title, boca::Bounds<float> const&)
{
    INFO(title);
//     if (bounds) {
//         bounds_.SetY(bounds);
//         bounds_.ResetX();
//         for (auto const & graph : graphs_) {
//             std::vector<double> xs(graph.GetX(), graph.GetX() + graph.GetMaxSize());
//             std::vector<double> ys(graph.GetY(), graph.GetY() + graph.GetMaxSize());
//             bounds_.WidenX(bounds, xs, ys);
//         }
//     }
    AddGraphs();
    if (!multi_graph_.GetYaxis()) return;
    INFO("set title",bounds_.Vertical().Floor(),bounds_.Vertical().Ceil());
    SetTitle(*multi_graph_.GetYaxis(), title);
    multi_graph_.GetYaxis()->SetLimits(bounds_.Vertical().Floor(), bounds_.Vertical().Ceil());
    multi_graph_.SetMinimum(bounds_.Vertical().Floor());
    multi_graph_.SetMaximum(bounds_.Vertical().Ceil());
    SetLog(bounds_.Vertical());
}

Bounds<double> Graphs::BoundsY()
{
    Info0;
    if (!multi_graph_.GetYaxis()) return {};
    return {multi_graph_.GetYaxis()->GetXmin(), multi_graph_.GetYaxis()->GetXmax()};
}

Bounds<double> Graphs::BoundsX()
{
    Info0;
    if (!multi_graph_.GetXaxis()) return {};
    return {multi_graph_.GetXaxis()->GetXmin(), multi_graph_.GetXaxis()->GetXmax()};
}

void Graphs::AddGraphs()
{
    Info0;
    Draw();
    if (multi_graph_.GetListOfGraphs()) return;
    for (auto & graph : graphs_) {
        multi_graph_.Add(&graph);
        legend_.AddEntry(graph, graph.GetTitle());
    }
}

void Graphs::AddLine(float x_value)
{
    INFO(x_value);
    if (!BoundsX().Inside(x_value)) return;
    Bounds<double> y = BoundsY();
    TLine line(x_value, y.Min(), x_value, y.Max());
    SetLine(line, graphs_.size() + lines_.size());
    lines_.emplace_back(line);
}

}
