

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>

#include "TAxis.h"
#include "TExec.h"

#include "physics/Math.hh"
#include "plotting/Style.hh"
#include "plotting/Legend.hh"
#include "plotting/Result.hh"
#include "plotting/Profile.hh"
#include "plotting/Graph.hh"

#include "Debug.hh"

namespace boca
{

Profile::Profile(const std::string& path, const std::string& name, bool show_title):
    Canvas(path, name, show_title)
{
//     if (show_title) histogram_.SetTitle(Title().c_str());
}

Profile::~Profile()
{
    SaveAs(FileName());
//   mkdir(Tagger().ExportFolderName().c_str(), 0700);
//   SaveAs(Tagger().ExportFolderName() + "/" + "Prof-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y);
}

void Profile::SetLegend(boca::Orientation orientation, const std::string& title)
{
    legend_.SetOrientation(orientation, title);
}

void Profile::SetLegend(Rectangle<float> const& rectangle, std::string const& title)
{
    legend_.Set(rectangle);
}

void Profile::Draw()
{
//     histogram_.Draw("nostack");
    legend_.Draw();
}

void Profile::SetXAxis(const std::string& title, const boca::Bounds<float>& limits)
{
    Draw();
    SetTitle(*profile_.GetXaxis(), title.c_str());
    if (limits) profile_.GetXaxis()->SetLimits(limits.Min(), limits.Max());

}

void Profile::SetYAxis(const std::string& title, const boca::Bounds<float>& limits)
{
    Draw();
    SetLog(limits);
    SetTitle(*profile_.GetYaxis(), title.c_str());
    if (limits) {
        profile_.GetYaxis()->SetLimits(limits.Min(), limits.Max());
        profile_.SetMinimum(limits.Min());
        profile_.SetMaximum(limits.Max());
    };

}

void Profile::SetDimensions(const std::string& name, int bins, Rectangle<float> const& bounds)
{
    //TProfile2D profile("", Tagger().LatexName().c_str(), bin_number, min.X(), max.X(), bin_number, min.Y(), max.Y());
    profile_.SetBins(bins, bounds.XMin(), bounds.XMax());
    profile_.SetName(name.c_str());
//     profile_.GetXaxis()->SetMinimum(min.X());
//     profile_.GetYaxis()->SetMinimum(min.Y());
//     profile_.GetXaxis()->SetMaximum(max.X());
//     profile_.GetYaxis()->SetMaximum(max.Y());
}

void Profile::SetProfile(Plot const& signal, Plot const& background)
{
    Info0;
    float max = (*boost::range::max_element(signal.Data(), [](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Z() < b.Z();
    })).Z();
    float min = (*boost::range::min_element(background.Data(), [](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Z() < b.Z();
    })).Z();
    for (auto const & point : signal.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    for (auto const & point : background.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    Color().Heat();
//   CommonHist(histogram, signal, kRed);
    profile_.SetMarkerColor(kRed);
    profile_.SetLineColor(kRed);
    SetTitle(*profile_.GetXaxis(), signal.XAxis().LatexName().c_str());
    SetTitle(*profile_.GetYaxis(), signal.YAxis().LatexName().c_str());
    SetTitle(*profile_.GetZaxis(), "BDT");

    //     profile_.SetZTitle("BDT");
    profile_.SetMaximum(max);
    profile_.SetMinimum(min);
    profile_.SetContour(30);
    profile_.Draw("colz");
}
Legend& Profile::Legend()
{
    return legend_;
}

}
