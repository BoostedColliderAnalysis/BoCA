/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm_ext/erase.hpp>

#include "TAxis.h"

#include "plotting/Style.hh"
#include "plotting/Graphs.hh"
// #define INFORMATION
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
    bounds_.UpdateX(MinMax(boost::remove_erase(xs2, 0)));
    std::vector<float> ys2 = ys;
    bounds_.UpdateY(MinMax(boost::remove_erase(ys2, 0)));
    TGraph graph(xs.size(), &xs.front(), &ys.front());
    SetLine(graph, graphs_.size());
    graph.SetTitle(name.c_str());
    graphs_.emplace_back(graph);
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
//         bounds_.ResetY();
//         Error(bounds.Min(), bounds.Max(), bounds_.XMin(), bounds_.XMax());
//         for (auto const & graph : graphs_) {
//             std::vector<double> x(graph.GetX(), graph.GetX() + graph.GetMaxSize());
//             std::vector<double> y(graph.GetY(), graph.GetY() + graph.GetMaxSize());
//             x = boost::remove_erase(x, 0);
//             bounds_.UpdateYMin(y.at(LowerBound(x, double(bounds_.XMin()))));
//             bounds_.UpdateYMax(y.at(UpperBound(x, double(bounds_.XMax()))));
//         }
    }
    AddGraphs();
    if (!multi_graph_.GetXaxis()) return;
    SetTitle(*multi_graph_.GetXaxis(), title.c_str());
    multi_graph_.GetXaxis()->SetLimits(bounds_.Horizontal().Floor(), bounds_.Horizontal().Ceil());
}

void Graphs::SetYAxis(std::string const& title, boca::Bounds<float> const& bounds)
{
    INFO(title);
    if (bounds) {
        bounds_.UpdateY(bounds);
//         for (auto const & graph : graphs_) {
//             std::vector<double> x(graph.GetX(), graph.GetX() + graph.GetMaxSize());
//             std::vector<double> y(graph.GetY(), graph.GetY() + graph.GetMaxSize());
//             y = boost::remove_erase(y, 0);
//             bounds_.UpdateXMin(x.at(LowerBound(y, double(bounds_.YMin()))));
//             bounds_.UpdateXMax(x.at(UpperBound(y, double(bounds_.YMax()))));
//         }
    }
    AddGraphs();
    if (!multi_graph_.GetYaxis()) return;
    SetTitle(*multi_graph_.GetYaxis(), title.c_str());
    multi_graph_.GetYaxis()->SetLimits(bounds_.Vertical().Floor(), bounds_.Vertical().Ceil());
    multi_graph_.SetMinimum(bounds_.Vertical().Floor());
    multi_graph_.SetMaximum(bounds_.Vertical().Ceil());
    SetLog(bounds_.Vertical());
}

Bounds<double> Graphs::LimitsY()
{
    Info0;
    if (!multi_graph_.GetYaxis()) return {};
    return {multi_graph_.GetYaxis()->GetXmin(), multi_graph_.GetYaxis()->GetXmax()};
}

Bounds<double> Graphs::LimitsX()
{
  Info0;
  if (!multi_graph_.GetXaxis()) return {};
  return {multi_graph_.GetXaxis()->GetXmin(), multi_graph_.GetXaxis()->GetXmax()};
}

void Graphs::AddGraphs()
{
    Info0;
    if (multi_graph_.GetListOfGraphs()) return;
    for (auto & graph : graphs_) {
        multi_graph_.Add(&graph);
        legend_.AddEntry(graph, graph.GetTitle());
    }
    Draw();
}

void Graphs::AddLine(float x_value)
{
    INFO(x_value);
    if (!LimitsX().Inside(x_value)) return;
    Bounds<double> y = LimitsY();
    TLine line(x_value, y.Min(), x_value, y.Max());
    SetLine(line, graphs_.size() + lines_.size());
    lines_.emplace_back(line);
}

}
