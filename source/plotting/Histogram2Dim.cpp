/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "plotting/Style.hh"
#include "plotting/Histogram2Dim.hh"

#include "Debug.hh"

namespace boca
{

Histogram2Dim::Histogram2Dim(std::string const& path, std::string const& name, bool show_title):
    Canvas(path, name, show_title)
{
//     if (show_title) histogram_.SetTitle(Title().c_str());
}

Histogram2Dim::~Histogram2Dim()
{
    SaveAs(FileName());
}

void Histogram2Dim::SetLegend(boca::Orientation orientation, std::string const& title)
{
    legend_.SetOrientation(orientation, title);
}

void Histogram2Dim::SetLegend(Rectangle<float> const& rectangle, std::string const& title)
{
    legend_.Set(rectangle);
}

void Histogram2Dim::Draw()
{
//     histogram_.Draw("nostack");
    legend_.Draw();
}

void Histogram2Dim::SetXAxis(std::string const& title, Bounds<float> const& bounds)
{
    Draw();
    for (auto & histogram : histograms_) {
        SetTitle(*histogram.GetXaxis(), title.c_str());
        if (bounds) histogram.GetXaxis()->SetLimits(bounds.Min(), bounds.Max());
    }
}

void Histogram2Dim::SetYAxis(std::string const& title, Bounds<float> const& bounds)
{
    Draw();
    SetLog(bounds);
    for (auto & histogram : histograms_) {
        SetTitle(*histogram.GetYaxis(), title.c_str());
        if (bounds) {
            histogram.GetYaxis()->SetLimits(bounds.Min(), bounds.Max());
            histogram.SetMinimum(bounds.Min());
            histogram.SetMaximum(bounds.Max());
        };
    }
}


void Histogram2Dim::AddHistogram(std::string const& name, int bins, Rectangle<float> const& bounds, std::vector<Vector3<float>> const& points, EColor color)
{
    Info0;
    TH2F histogram("", name.c_str(), bins, bounds.XMin(), bounds.XMax(), bins, bounds.YMin(), bounds.YMax());

    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (auto const & point : points) histogram.Fill(point.X(), point.Y());
    histogram.SetContour(20);

//   CommonHist(histogram, plot, color);
    SetExec(color);

    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
//   SetAxis(*histogram.GetXaxis(), plot.nice_name_x.c_str());
//   SetAxis(*histogram.GetYaxis(), plot.nice_name_y.c_str());

    histogram.Draw(options.c_str());
    histograms_.emplace_back(histogram);
}

void Histogram2Dim::SetExec(EColor color)
{
    TExec exec;
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
    execs_.emplace_back(exec);
}
Legend& Histogram2Dim::Legend()
{
    return legend_;
}


}
