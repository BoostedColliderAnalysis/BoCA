

#include "TAxis.h"
#include "TExec.h"

#include "physics/Math.hh"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"
#include "plotting/Histogram2Dim.hh"
#include "plotting/Graph.hh"

#include "Debug.hh"

namespace boca
{

Histogram2Dim::Histogram2Dim(const std::string& path, const std::string& name, bool show_title):
    Canvas(path, name, show_title)
{
//     if (show_title) histogram_.SetTitle(Title().c_str());
}

Histogram2Dim::~Histogram2Dim()
{
    SaveAs(FileName());
}

void Histogram2Dim::SetLegend(boca::Orientation orientation, const std::string& title)
{
    legend_.SetOrientation(orientation, title);
}

void Histogram2Dim::SetLegend(Vector2<float> const& point, float width, float height, std::string const& title)
{
  legend_.Set(point, width, height);
}

void Histogram2Dim::Draw()
{
//     histogram_.Draw("nostack");
    legend_.Draw();
}

void Histogram2Dim::SetXAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    for (auto & histogram : histograms_) {
        SetTitle(*histogram.GetXaxis(), title.c_str());
        if (limits) histogram.GetXaxis()->SetLimits(limits.Min(), limits.Max());
    }
}

void Histogram2Dim::SetYAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetLog(limits);
    for (auto & histogram : histograms_) {
        SetTitle(*histogram.GetYaxis(), title.c_str());
        if (limits) {
            histogram.GetYaxis()->SetLimits(limits.Min(), limits.Max());
            histogram.SetMinimum(limits.Min());
            histogram.SetMaximum(limits.Max());
        };
    }
}


void Histogram2Dim::AddHistogram(std::string const& name, int bins,  Vector2<float> const& min, Vector2<float> const& max, std::vector<Vector3<float>> const& points, EColor color)
{
    Info0;
    TH2F histogram("", name.c_str(), bins, min.X(), max.X(), bins, min.Y(), max.Y());

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


}
