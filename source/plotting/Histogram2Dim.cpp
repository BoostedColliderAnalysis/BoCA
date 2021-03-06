/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <sys/stat.h>
#include "boca/plotting/Style.hh"
#include "boca/plotting/Histogram2Dim.hh"
#include "boca/plotting/Font.hh"
#include "boca/plotting/Colors.hh"
#include "boca/generic/Vector.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

using namespace std::string_literals;

Histogram2Dim::Histogram2Dim(std::string const& path, std::string const& name, bool show_title):
    Canvas(path, name, show_title)
{
    INFO0;
    mkdir(path.c_str(), 0700);
//     if (show_title) histogram_.SetTitle(Title().c_str());
}

Histogram2Dim::~Histogram2Dim()
{
    Draw();
    SaveAs(FileName());
}

void Histogram2Dim::SetLegend(boca::Orientation orientation, latex::String const& title)
{
    INFO0;
    canvas().SetTopMargin(TextHeight() * 2);
    for (auto & histogram : histograms_) legend_.AddEntry(histogram, histogram.GetName());
    legend_.TwoColumn();
    legend_.SetOrientation(orientation, title);
}

void Histogram2Dim::Draw()
{
    INFO0;
    auto options = "cont1"s;
    auto first = true;
    for (auto & histogram : histograms_) {
        histogram.Draw(options.c_str());
        execs_.at(Position(histograms_, histogram)).Draw();
        if (first) options += " same";
    }
    legend_.Draw();
}

void Histogram2Dim::SetXAxis(latex::String const& title)
{
    INFO0;
    for (auto & histogram : histograms_) SetAxis(*histogram.GetXaxis(), title);
}

void Histogram2Dim::SetYAxis(latex::String const& title)
{
    INFO0;
    for (auto & histogram : histograms_) SetAxis(*histogram.GetYaxis(), title);
}

void Histogram2Dim::AddHistogram(latex::String const& name, int bins, Rectangle<double> const& range, Plot const& plot, EColor color)
{
    INFO0;
    auto x_bin = static_cast<int>(plot.x_is_int ? std::floor(range.Width()) : bins);
    auto y_bin = static_cast<int>(plot.y_is_int ? std::floor(range.Height()) : bins);
    auto histogram = TH2F{name.str(latex::Medium::root).c_str(), "", x_bin, range.XMin(), range.XMax(), y_bin, range.YMin(), range.YMax()};
    for (auto const & point : plot.Data()) histogram.Fill(point.X(), point.Y());
    histogram.SetContour(20);
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
    histograms_.emplace_back(histogram);
    execs_.emplace_back(Exec(color));
}

TExec Histogram2Dim::Exec(EColor color)
{
    INFO0;
    auto exec = TExec{};
    switch (color) {
    case kRed : exec.SetAction(Red::Action().c_str());
        break;
    case kBlue : exec.SetAction(Blue::Action().c_str());
        break;
        DEFAULT(color);
    }
    return exec;
}

Legend& Histogram2Dim::Legend()
{
    return legend_;
}
std::string Histogram2Dim::FileBaseName() const
{
    return Path() + "/" + Title() ;
}


}
