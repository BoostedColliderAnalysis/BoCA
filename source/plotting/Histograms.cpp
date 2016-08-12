/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/plotting/Style.hh"
#include "boca/plotting/Histograms.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Histograms::Histograms() :
    Canvas()
{}

Histograms::Histograms(std::string const& path, std::string const& name, bool show_title) :
    Canvas(path, name, show_title)
{
    INFO(name);
    if (show_title) stack_.SetTitle(Title().c_str());
}

Histograms::~Histograms()
{
    INFO0;
    Draw();
    SaveAs(FileName());
}

void Histograms::AddHistogram(std::vector<double> const& values, Names const& names, Range<double> const& range, bool is_int)
{
    INFO0;
    range_.WidenX(range);
    auto min = FloorToDigits(range.Min(), 1);
    auto max = CeilToDigits(range.Max(), 1);
    int bins = is_int ? max - min : 50;
    TH1F histogram(names.Name().c_str(), names.LatexName().str(latex::Medium::root).c_str(), bins, min , max);
    INFO(names.LatexName().str(latex::Medium::root).c_str(), histogram.GetTitle());
    for (auto const & bdt : values) histogram.Fill(bdt);
    if (histogram.Integral() != 0) histogram.Scale(1. / histogram.Integral());
    SetLine(histogram, histograms_.size());
    histograms_.emplace_back(histogram);
}

void Histograms::AddHistogram(std::vector<double> const& values, Names const& names, Rectangle<double> const& range)
{
    INFO0;
    range_.WidenY(range.Vertical());
    AddHistogram(values, names, range.Horizontal());
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
    for (auto & line : lines_) {
//         line.SetY1(RangeY().Min());
        line.SetY1(stack_.GetMinimum());
        DEBUG(RangeY().Max(), stack_.GetMaximum());
//         line.SetY2(RangeY().Max() * 0.5);
        line.SetY2(stack_.GetMaximum() * 0.625);
        line.Draw();
    }
    legend_.Draw();
}

void Histograms::SetXAxis(latex::String const& title, boca::Range<double> const& range)
{
    INFO(title.str(latex::Medium::root));
    AddHistograms();
    if (!stack_.GetXaxis()) return;
    SetAxis(*stack_.GetXaxis(), title);
    if (range) stack_.GetXaxis()->SetLimits(range.Min(), range.Max());
}

void Histograms::SetYAxis(latex::String const& title, boca::Range<double> const& range)
{
    INFO(title.str(latex::Medium::root));
    AddHistograms();
    if (!stack_.GetYaxis()) return;
    SetAxis(*stack_.GetYaxis(), title);
    if (range) {
//         SetLog(range);
        stack_.GetYaxis()->SetLimits(range.Min(), range.Max());
        stack_.SetMinimum(range.Min());
        stack_.SetMaximum(range.Max());
    }
//     else SetLog(RangeY());
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
    for (auto & histogram : histograms_) {
        stack_.Add(&histogram);
        INFO(histogram.GetTitle(), histograms_.size());
        if (histograms_.size() > 1) legend_.AddEntry(histogram, histogram.GetTitle());
    }
    Draw();
}

void Histograms::AddLine(double x_value, std::string const& title)
{
    INFO(title, x_value);
    if (!range_.Horizontal().Inside(x_value)) return;
    auto y = RangeY();
    INFO(y.Max());
    TLine line(x_value, y.Min(), x_value, y.Max() * 0.5);
    SetLine(line, histograms_.size() + lines_.size() + 1);
    if (x_value != 0) line.Draw();
    if (!title.empty()) legend_.AddEntry(line, title);
    lines_.emplace_back(line);
}

}
