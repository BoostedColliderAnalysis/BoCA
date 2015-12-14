

#include "TAxis.h"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"

#include "plotting/Graphs.hh"
#include "Debug.hh"

namespace boca
{

Graphs::Graphs(const std::string& path, const std::string& name, bool show_title):
    Canvas(path, name, show_title)
{
    if (show_title) multi_graph_.SetTitle(Title().c_str());
}

Graphs::~Graphs()
{
  SaveAs(FileName());
}

void Graphs::AddGraph(std::vector<float> const& xs, std::vector<float> const& ys, std::string const& name)
{
    Check(xs.size() == ys.size(), xs.size(), ys.size());
    TGraph graph(xs.size(), &xs.front(), &ys.front());
    SetLine(graph, graphs_.size());
    graph.SetTitle(name.c_str());
    graphs_.emplace_back(graph);
}

void Graphs::SetLegend(boca::Orientation orientation, const std::string& title)
{
    AddGraphs();
    legend_.SetOrientation(orientation, title);
}

void Graphs::Draw()
{
    multi_graph_.Draw("al");
    legend_.Draw();
}

void Graphs::SetXAxis(const std::string& title, const boca::Bounds<float>& bounds)
{
    Draw();
    SetTitle(*multi_graph_.GetXaxis(), title.c_str());
    if (bounds) multi_graph_.GetXaxis()->SetLimits(bounds.Min(), bounds.Max());
}

void Graphs::SetYAxis(const std::string& title, const boca::Bounds<float>& bounds)
{
    Draw();
    SetTitle(*multi_graph_.GetYaxis(), title.c_str());
    if (bounds) {
        multi_graph_.GetYaxis()->SetLimits(bounds.Min(), bounds.Max());
        multi_graph_.SetMinimum(bounds.Min());
        multi_graph_.SetMaximum(bounds.Max());
        SetLog(bounds);
    }
//     else SetLog();
}

Bounds<double> Graphs::LimitsY()
{
    TAxis& axis = *multi_graph_.GetYaxis();
    return {axis.GetXmin(), axis.GetXmax()};
}

void Graphs::AddGraphs()
{
    if (multi_graph_.GetListOfGraphs() && multi_graph_.GetListOfGraphs()->GetSize() != graphs_.size() && multi_graph_.GetListOfGraphs()->GetSize() != graphs_.size() + 1) return;
    for (auto & graph : graphs_) {
        multi_graph_.Add(&graph);
        legend_.AddEntry(graph, graph.GetTitle());
    }
}

void Graphs::AddLine(float x_value)
{
    Bounds<double> y = LimitsY();
    TLine line(x_value, y.Min(), x_value, y.Max());
    SetLine(line, graphs_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    lines_.emplace_back(line);
}

}
