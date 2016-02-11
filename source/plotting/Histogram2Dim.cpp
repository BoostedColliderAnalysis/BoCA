/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <sys/stat.h>
#include "plotting/Style.hh"
#include "plotting/Histogram2Dim.hh"
#include "plotting/Font.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

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

void Histogram2Dim::SetLegend(boca::Orientation orientation, std::string const& title)
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
    std::string options = "cont1";
    bool first = true;
    for (auto & histogram : histograms_) {
        histogram.Draw(options.c_str());
        execs_.at(&histogram - &histograms_.front()).Draw();
        if (first) options += " same";
    }
    legend_.Draw();
}

void Histogram2Dim::SetXAxis(std::string const& title)
{
    INFO0;
    for (auto & histogram : histograms_) SetTitle(*histogram.GetXaxis(), title.c_str());
}

void Histogram2Dim::SetYAxis(std::string const& title)
{
    INFO0;
    for (auto & histogram : histograms_) SetTitle(*histogram.GetYaxis(), title.c_str());
}

void Histogram2Dim::AddHistogram(std::string const& name, int bins, Rectangle<float> const& range, Plot const& plot, EColor color)
{
    INFO0;
    int x_bin = plot.x_is_int ? std::floor(range.Width()) : bins;
    int y_bin = plot.y_is_int ? std::floor(range.Height()) : bins;
    TH2F histogram(name.c_str(), "", x_bin, range.XMin(), range.XMax(), y_bin, range.YMin(), range.YMax());
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
    TExec exec;
    switch (color) {
    case kRed : exec.SetAction("boca::Color().Red();");
        break;
    case kBlue : exec.SetAction("boca::Color().Blue();");
        break;
    default : ERROR("unsupported color");
    }
    return exec;
}

Legend& Histogram2Dim::Legend()
{
    return legend_;
}
std::__cxx11::string Histogram2Dim::FileBaseName() const
{
    return Path() + "/" + Title() ;
}


}
