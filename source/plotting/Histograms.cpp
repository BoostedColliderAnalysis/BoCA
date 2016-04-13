/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TAxis.h"

#include "plotting/Style.hh"
#include "plotting/Histograms.hh"
// #define INFORMATION
#include "generic/DEBUG.hh"

namespace boca
{

Histograms::Histograms() :
    Canvas()
{}

Histograms::Histograms(std::string const& path, std::string const& name, bool show_title)
// :
//     Canvas(path, name, show_title)
{
    INFO(name);
//     if (show_title) stack_.SetTitle(Title().c_str());
    Initialize(path, name, show_title);
}

Histograms::~Histograms()
{
    INFO0;
    Draw();
    SaveAs(FileName());
}

void Histograms::Initialize(std::string const& path, std::string const& name, bool show_title)
{
    INFO(name);
    Canvas::Initialize(path, name, show_title);
    if (show_title) stack_.SetTitle(Title().c_str());
}

void Histograms::AddHistogram(std::vector<double> const& values, std::string const& name, Range<double> const& range, bool is_int)
{
    INFO(name);
    range_.WidenX(range);
    auto min = FloorToDigits(range.Min(), 1);
    auto max = CeilToDigits(range.Max(), 1);
    int bins = is_int ? max - min : 50;
    TH1F histogram(name.c_str(), "", bins, min , max);
    for (auto const & bdt : values) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetLine(histogram, histograms_.size());
    histogram.SetTitle(name.c_str());
    histograms_.emplace_back(histogram);
}

void Histograms::AddHistogram(std::vector<double> const& values, std::string const& name, Rectangle<double> const& range)
{
    INFO(name);
    range_.WidenY(range.Vertical());
    AddHistogram(values, name, range.Horizontal());
}

void Histograms::SetLegend(boca::Orientation orientation, std::string const& title)
{
    INFO(title);
    AddHistograms();
    legend_.SetOrientation(orientation, title);
    if (is(orientation, Orientation::outside | Orientation::right)) canvas().SetRightMargin(legend_.Rectangle().Width() * 1.2);
}

void Histograms::Draw()
{
    INFO0;
    stack_.Draw("nostack");
    legend_.Draw();
    for (auto & line : lines_) {
        line.SetY1(RangeY().Min());
        line.SetY2(RangeY().Max());
        line.Draw();
    }
}

void Histograms::SetXAxis(std::string const& title, boca::Range<double> const& range)
{
    INFO(title);
    AddHistograms();
    if (!stack_.GetXaxis()) return;
    SetAxis(*stack_.GetXaxis(), title.c_str());
    if (range) stack_.GetXaxis()->SetLimits(range.Min(), range.Max());
}

void Histograms::SetYAxis(std::string const& title, boca::Range<double> const& range)
{
    INFO(title);
    AddHistograms();
    if (!stack_.GetYaxis()) return;
    SetAxis(*stack_.GetYaxis(), title.c_str());
    if (range) {
        SetLog(range);
        stack_.GetYaxis()->SetLimits(range.Min(), range.Max());
        stack_.SetMinimum(range.Min());
        stack_.SetMaximum(range.Max());
    } else SetLog(RangeY());
}

Range<double> Histograms::RangeY()
{
    INFO0;
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
    INFO(histograms_.size(), stack_.GetHists());
    if (stack_.GetHists()) return;
    for (auto & graph : histograms_) {
        stack_.Add(&graph);
        if (histograms_.size() > 1) legend_.AddEntry(graph, graph.GetTitle());
    }
    Draw();
}

void Histograms::AddLine(double x_value, std::string const& title)
{
    INFO(title);
    if (!RangeX().Inside(x_value)) return;
    auto y = RangeY();
    TLine line(x_value, y.Min(), x_value, y.Max() * 1.05);
    SetLine(line, histograms_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    if (!title.empty()) legend_.AddEntry(line, title);
    lines_.emplace_back(line);
}

}
