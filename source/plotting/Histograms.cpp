

#include "TAxis.h"
#include "Debug.hh"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"
#include "physics/Math.hh"

#include "plotting/Histograms.hh"

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

void Histograms::AddHistogram(std::vector<float> const& values, std::string const& name, Limits<float>& limits_x, Limits<float>& limits_y)
{
    TH1F histogram(name.c_str(), "", 50, FloorToDigits(limits_x.Min(), 1), CeilToDigits(limits_x.Max(), 1));
    for (auto const & bdt : values) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetStyle(histogram, histograms_.size());
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > limits_y.Max()) limits_y.SetMax(max_0);
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

void Histograms::SetXAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetTitle(*stack_.GetXaxis(), title.c_str());
    if (limits) stack_.GetXaxis()->SetLimits(limits.Min(), limits.Max());
}

void Histograms::SetYAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetLog(limits);
    SetTitle(*stack_.GetYaxis(), title.c_str());
    if (limits) {
        stack_.GetYaxis()->SetLimits(limits.Min(), limits.Max());
        stack_.SetMinimum(limits.Min());
        stack_.SetMaximum(limits.Max());
    } else SetLog(LimitsY());
}

Limits<double> Histograms::LimitsY()
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
    Limits<double> y = LimitsY();
    TLine line(x_value, y.Min(), x_value, y.Max() * 1.05);
    SetStyle(line, histograms_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    lines_.emplace_back(line);
}

}
