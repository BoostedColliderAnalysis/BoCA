/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TAxis.h"

#include "plotting/Style.hh"
#include "plotting/Histograms.hh"

#include "Debug.hh"

namespace boca
{

Histograms::Histograms(std::string const& path, std::string const& name, bool show_title):
    Canvas(path, name, show_title)
{
    INFO0;
    if (show_title) stack_.SetTitle(Title().c_str());
}

Histograms::~Histograms()
{
    INFO0;
    Draw();
    SaveAs(FileName());
}

void Histograms::AddHistogram(std::vector<float> const& values, std::string const& name, Rectangle<float> const& range)
{
    INFO(name);
    TH1F histogram(name.c_str(), "", 50, FloorToDigits(range.XMin(), 1), CeilToDigits(range.XMax(), 1));
    for (auto const & bdt : values) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetLine(histogram, histograms_.size());
//     float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
//     if (max_0 > range.YMax()) range.SetYMax(max_0);
    range_.Widen(range);
    histogram.SetTitle(name.c_str());
    histograms_.emplace_back(histogram);
}

void Histograms::SetLegend(boca::Orientation orientation, std::string const& title)
{
    INFO(title);
    AddHistograms();
    legend_.SetOrientation(orientation, title);
}

void Histograms::Draw()
{
    INFO0;
    stack_.Draw("nostack");
    if (histograms_.size() > 1) legend_.Draw();
    for (auto & line : lines_) line.Draw();
}

void Histograms::SetXAxis(std::string const& title, boca::Range<float> const& range)
{
    AddHistograms();
    SetTitle(*stack_.GetXaxis(), title.c_str());
    if (range) stack_.GetXaxis()->SetLimits(range.Min(), range.Max());
}

void Histograms::SetYAxis(std::string const& title, boca::Range<float> const& range)
{
    AddHistograms();
    SetTitle(*stack_.GetYaxis(), title.c_str());
    if (range) {
        SetLog(range);
        stack_.GetYaxis()->SetLimits(range.Min(), range.Max());
        stack_.SetMinimum(range.Min());
        stack_.SetMaximum(range.Max());
    } else SetLog(RangeY());
}

Range<double> Histograms::RangeY()
{
    if (!stack_.GetYaxis()) return {};
    return {stack_.GetYaxis()->GetXmin(), stack_.GetYaxis()->GetXmax()};
}

Range<double> Histograms::RangeX()
{
  INFO0;
  if (!stack_.GetXaxis()) return {};
  return {stack_.GetXaxis()->GetXmin(), stack_.GetXaxis()->GetXmax()};
}

void Histograms::AddHistograms()
{
    if (stack_.GetHists()) return;
    for (auto & graph : histograms_) {
        stack_.Add(&graph);
        legend_.AddEntry(graph, graph.GetTitle());
    }
    Draw();
}

void Histograms::AddLine(float x_value)
{
    if (!RangeX().Inside(x_value)) return;
    Range<double> y = RangeY();
    TLine line(x_value, y.Min(), x_value, y.Max() * 1.05);
    SetLine(line, histograms_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    lines_.emplace_back(line);
}

}
