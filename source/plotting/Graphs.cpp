

#include "TAxis.h"
#include "Debug.hh"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"

#include "plotting/Graphs.hh"

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
    SetPlotStyle(graph, graphs_.size());
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

void Graphs::SetXAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetAxis(*multi_graph_.GetXaxis(), title.c_str());
    if (limits) multi_graph_.GetXaxis()->SetLimits(limits.Min(), limits.Max());
}

void Graphs::SetYAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetAxis(*multi_graph_.GetYaxis(), title.c_str());
    if (limits) {
        SetLog(limits);
        multi_graph_.GetYaxis()->SetLimits(limits.Min(), limits.Max());
        multi_graph_.SetMinimum(limits.Min());
        multi_graph_.SetMaximum(limits.Max());
    } else SetLog(LimitsY());
}

Limits<double> Graphs::LimitsY()
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
    Limits<double> y = LimitsY();
    TLine line(x_value, y.Min(), x_value, y.Max());
    SetPlotStyle(line, graphs_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    lines_.emplace_back(line);
}

}
