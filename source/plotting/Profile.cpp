

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

void Profile::SetLegend(Point const& point, float width, float height, std::string const& title)
{
    legend_.Set(point, width, height);
}

void Profile::Draw()
{
//     histogram_.Draw("nostack");
    legend_.Draw();
}

void Profile::SetXAxis(const std::string& title, const boca::Limits<float>& limits)
{
    Draw();
    SetTitle(*profile_.GetXaxis(), title.c_str());
    if (limits) profile_.GetXaxis()->SetLimits(limits.Min(), limits.Max());

}

void Profile::SetYAxis(const std::string& title, const boca::Limits<float>& limits)
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

void Profile::SetDimensions(const std::string& name, int bins, const Point& min, const Point& max)
{
    //TProfile2D profile("", Tagger().LatexName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
  profile_.SetBins(bins,min.x,max.x);
    profile_.SetName(name.c_str());
//     profile_.GetXaxis()->SetMinimum(min.x);
//     profile_.GetYaxis()->SetMinimum(min.y);
//     profile_.GetXaxis()->SetMaximum(max.x);
//     profile_.GetYaxis()->SetMaximum(max.y);
}

void Profile::SetProfile(Plot const& signal, Plot const& background)
{
    Info0;
    float max = (*boost::range::max_element(signal.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    float min = (*boost::range::min_element(background.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    for (auto const & point : signal.points) profile_.Fill(point.x, point.y, point.z);
    for (auto const & point : background.points) profile_.Fill(point.x, point.y, point.z);
    Color().Heat();
//   CommonHist(histogram, signal, kRed);
    profile_.SetMarkerColor(kRed);
    profile_.SetLineColor(kRed);
    SetTitle(*profile_.GetXaxis(), signal.nice_name_x.c_str());
    SetTitle(*profile_.GetYaxis(), signal.nice_name_y.c_str());
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
