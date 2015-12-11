#include "plotting/Graph.hh"

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "THStack.h"
#include "TList.h"
#include "TMultiGraph.h"
#include "TH2.h"
#include "TH1.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TExec.h"
#include "TLatex.h"
#include "TNamed.h"

#include "physics/Math.hh"
#include "plotting/Canvas.hh"
#include "plotting/Font.hh"
#include "plotting/Style.hh"
#include "plotting/Result.hh"
#include "plotting/Font.hh"
#include "plotting/Legend.hh"
#include "plotting/Graphs.hh"
#include "Debug.hh"

namespace boca
{

TH1F Histogram(Result const& result, Point& max, Point const& min, int index)
{
    TH1F histogram(result.info_branch_.Name.c_str(), "", 50, FloorToDigits(min.x, 1), CeilToDigits(max.x, 1));
    for (auto const & bdt : result.bdt) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetPlotStyle(histogram, index);
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > max.y) max.y = max_0;
    return histogram;
}

void AddHistogram(THStack& stack, TH1& histogram, Legend& legend)
{
    stack.Add(&histogram);
    legend.AddEntry(histogram, histogram.GetName());
}

TLine Line(float bin, float y_min, float y_max, int index)
{
    TLine line(Results::XValue(bin), y_min, Results::XValue(bin), y_max);
    SetPlotStyle(line, index);
    if (bin != 0) line.Draw();
    return line;
}

TLine Line(float bin, Limits const& y, int index)
{
  TLine line(Results::XValue(bin), y.Min(), Results::XValue(bin), y.Max());
  SetPlotStyle(line, index);
  if (bin != 0) line.Draw();
  return line;
}

void AddGraph(TGraph& graph, TMultiGraph& multi_graph, Legend& legend, std::vector<std::string> const& names, int index)
{
    SetPlotStyle(graph, index);
    multi_graph.Add(&graph);
    legend.AddEntry(graph, names.at(index));
}

void SetMultiGraph(TMultiGraph& multi_graph, Point const& min, Point const& max)
{
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(min.x, max.x);
    multi_graph.SetMaximum(max.y);
    multi_graph.SetMinimum(min.y);
    SetAxis(*multi_graph.GetXaxis(), "Signal acceptance");
    SetAxis(*multi_graph.GetYaxis(), "Background acceptance");
}

TGraph Graph(Results const& results, std::vector<float> const& values, std::string const& title)
{
    TGraph graph(Result::steps, &results.x_values.front(), &values.front());
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    SetAxis(*graph.GetXaxis(), "BDT");
    SetAxis(*graph.GetYaxis(), title.c_str());
    return graph;
}

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec)
{
    Info0;
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (auto const & point : plot.points) histogram.Fill(point.x, point.y);
    histogram.SetContour(20);
    switch (color) {
    case kRed :
        exec.SetAction("boca::Color().Red();");
        break;
    case kBlue :
        exec.SetAction("boca::Color().Blue();");
        break;
    default:
        Error("unsupported color");
    }
    exec.Draw();
    CommonHist(histogram, plot, color);
    histogram.Draw(options.c_str());
}

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background)
{
    Info0;
    float max = (*boost::range::max_element(signal.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    float min = (*boost::range::min_element(background.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    for (auto const & point : signal.points) histogram.Fill(point.x, point.y, point.z);
    for (auto const & point : background.points) histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    CommonHist(histogram, signal, kRed);
    SetAxis(*histogram.GetZaxis(), "BDT");
//     histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void CommonHist(TH1& histogram, Plot const& plot, EColor color)
{
    Info0;
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
    SetAxis(*histogram.GetXaxis(), plot.nice_name_x.c_str());
    SetAxis(*histogram.GetYaxis(), plot.nice_name_y.c_str());
}





TGraph CutGraph(CutResults const& results, std::vector<float> const& values, std::string const& title)
{
    TGraph graph(results.signals.front().steps, &results.x_values.front(), &values.front());
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    SetAxis(*graph.GetXaxis(), "Signal efficiency");
    SetAxis(*graph.GetYaxis(), title.c_str());
    return graph;
}

TLine CutLine(float bin, float y_min, float y_max, int index)
{
    TLine line(bin, y_min, bin, y_max);
    SetPlotStyle(line, index);
    if (bin != 0) line.Draw();
    return line;
}


}
