# include "Graph.hh"

#include "THStack.h"
#include "TLegendEntry.h"
#include "TList.h"
#include "TMultiGraph.h"
#include "TH2.h"
#include "TExec.h"

#include "Math.hh"
#include "Canvas.hh"
#include "Result.hh"
#include "Debug.hh"

namespace boca{

TH1F Histogram(const Result& result, Point& max, Point& min, int index)
{
    TH1F histogram(result.info_branch_.Name.c_str(), "", 50, FloorToDigits(min.x, 1), CeilToDigits(max.x, 1));
    for (auto const & bdt : result.bdt) {
        histogram.Fill(bdt);
    }
    if (histogram.Integral() != 0) {
        histogram.Scale(1. / histogram.Integral());
    }
    Canvas::SetPlotStyle(histogram, index);
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > max.y) {
        max.y = max_0;
    }
    return histogram;
}

void AddHistogram(THStack& stack, TH1& histogram, TLegend& legend)
{
    stack.Add(&histogram);
    legend.AddEntry(&histogram, histogram.GetName(), "l");
}

TLegend Legend(const Point& min, float width, float height, const std::string& title)
{
    TLegend legend(min.x, min.y, min.x + width, min.y + height);
    if (!title.empty()) {
        legend.SetHeader(title.c_str());
        Canvas::SetTextStyle(static_cast<TLegendEntry&>(*legend.GetListOfPrimitives()->First()));
    }
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    Canvas::SetTextStyle(legend);
    legend.Draw();
    return legend;
}

TLegend Legend(Orientation orientation, const Strings& entries, const std::string& title)
{
    int letters = std::max_element(entries.begin(), entries.end(), [](std::string const & entry_1, std::string const & entry_2) {
        return entry_1.size() < entry_2.size();
    })->size();
    float letter_width = 0.01;
    float letter_height = 0.06;
    float image_width = 0.1;
    float width = letter_width * letters + image_width;
    float height = entries.size() * letter_height;
    if (!title.empty()) {
        height += letter_height;
    }
    // default values for Orientation::center
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 4; // FIXME why is this necessary; why not 1/2?
    float y_offset = height / 2;
    FlagSwitch(orientation, [&](Orientation orientation) {
        switch (orientation) {
        case Orientation::left:
            x_shift = 0;
            x_offset = 0;
            break;
        case Orientation::right:
            x_shift = 1;
            x_offset = width / 2; // FIXME why is this necessary; why not 1?
            break;
        case Orientation::top:
            y_shift = 1;
            y_offset = height;
            break;
        case Orientation::bottom:
            y_shift = 0;
            y_offset = 0;
            break;
        default : break;
        }
    });
    float margin = 0.03;
    float x_unit = 1 - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2 * margin;
    float y_unit = 1 - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2 * margin;
    Point min;
    min.x = gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset;
    min.y = gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset;
    return Legend(min, width, height, title);
}

TLine Line(float bin, float y_min, float y_max, int index)
{
    TLine line(Results::XValue(bin), y_min, Results::XValue(bin), y_max);
    Canvas::SetPlotStyle(line, index);
    if (bin != 0) {
        line.Draw();
    }
    return line;
}

void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, const boca::Strings& names, int index)
{
    Canvas::SetPlotStyle(graph, index);
    multi_graph.Add(&graph);
    legend.AddEntry(&graph, names.at(index).c_str(), "l");
}

void SetMultiGraph(TMultiGraph& multi_graph, const Point& min, const Point& max)
{
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(min.x, max.x);
    multi_graph.SetMaximum(max.y);
    multi_graph.SetMinimum(min.y);
    Canvas::SetAxis(*multi_graph.GetXaxis(), "Signal acceptance");
    Canvas::SetAxis(*multi_graph.GetYaxis(), "Background acceptance");
}

TGraph Graph(const Results& results, const std::vector< float >& values, const std::string& title)
{
    TGraph graph(Result::steps, &results.x_values.front(), &values.front());
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    Canvas::SetAxis(*graph.GetXaxis(), "BDT");
    Canvas::SetAxis(*graph.GetYaxis(), title.c_str());
    return graph;
}

void SetHistogram(TH2& histogram, const Plot& plot, EColor color, TExec& exec)
{
    Info();
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (auto const & point : plot.points) {
        histogram.Fill(point.x, point.y);
    }
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

void SetProfile(TH2& histogram, const Plot& signal, const Plot& background)
{
    Info();
    float max = (*std::max_element(signal.points.begin(), signal.points.end(), [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    float min = (*std::min_element(background.points.begin(), background.points.end(), [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    for (auto const & point : signal.points) {
        histogram.Fill(point.x, point.y, point.z);
    }
    for (auto const & point : background.points) {
        histogram.Fill(point.x, point.y, point.z);
    }
    Color().Heat();
    CommonHist(histogram, signal, kRed);
    histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void CommonHist(TH1& histogram, const Plot& plot, EColor color)
{
    Info();
    histogram.SetXTitle(plot.nice_name_x.c_str());
    histogram.SetYTitle(plot.nice_name_y.c_str());
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
}

}
