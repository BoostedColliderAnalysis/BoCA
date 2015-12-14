

#include "TAxis.h"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"
#include "physics/Math.hh"

#include "plotting/Histograms.hh"
#include "Debug.hh"

namespace boca
{

Histograms::Histograms(const std::string& path, const std::string& name, bool show_title):
    Canvas(path, name, show_title)
{
    if (show_title) stack_.SetTitle(Title().c_str());
}

Histograms::~Histograms()
{
    SaveAs(FileName());
}

void Histograms::AddHistogram(std::vector<float> const& values, std::string const& name, Rectangle<float>& bounds)
{
    TH1F histogram(name.c_str(), "", 50, FloorToDigits(bounds.XMin(), 1), CeilToDigits(bounds.XMax(), 1));
    for (auto const & bdt : values) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetLine(histogram, histograms_.size());
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > bounds.YMax()) bounds.SetYMax(max_0);
    histogram.SetTitle(name.c_str());
    histograms_.emplace_back(histogram);
}

void Histograms::SetLegend(boca::Orientation orientation, const std::string& title)
{
    AddHistograms();
    legend_.SetOrientation(orientation, title);
}

void Histograms::Draw()
{
    stack_.Draw("nostack");
    legend_.Draw();
}

void Histograms::SetXAxis(const std::string& title, const boca::Bounds<float>& bounds)
{
    Draw();
    SetTitle(*stack_.GetXaxis(), title.c_str());
    if (bounds) stack_.GetXaxis()->SetLimits(bounds.Min(), bounds.Max());
}

void Histograms::SetYAxis(const std::string& title, const boca::Bounds<float>& bounds)
{
    Draw();
    SetLog(bounds);
    SetTitle(*stack_.GetYaxis(), title.c_str());
    if (bounds) {
        stack_.GetYaxis()->SetLimits(bounds.Min(), bounds.Max());
        stack_.SetMinimum(bounds.Min());
        stack_.SetMaximum(bounds.Max());
    } else SetLog(LimitsY());
}

Bounds<double> Histograms::LimitsY()
{
    TAxis& axis = *stack_.GetYaxis();
    return {axis.GetXmin(), axis.GetXmax()};
}

void Histograms::AddHistograms()
{
    if (stack_.GetHists() && stack_.GetHists()->GetSize() != histograms_.size() && stack_.GetHists()->GetSize() != histograms_.size() + 1) return;
    for (auto & graph : histograms_) {
        stack_.Add(&graph);
        legend_.AddEntry(graph, graph.GetTitle());
    }
}

void Histograms::AddLine(float x_value)
{
    Bounds<double> y = LimitsY();
    TLine line(x_value, y.Min(), x_value, y.Max() * 1.05);
    SetLine(line, histograms_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    lines_.emplace_back(line);
}

}
