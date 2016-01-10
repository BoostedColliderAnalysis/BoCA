/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>

#include "Branches.hh"

#include "plotting/Style.hh"
#include "plotting/Profile.hh"

#include "Debug.hh"

namespace boca
{

Profile::Profile(std::string const& path, std::string const& name, bool show_title):
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

void Profile::SetLegend(boca::Orientation orientation, std::string const& title)
{
    legend_.SetOrientation(orientation, title);
}

void Profile::SetLegend(Rectangle<float> const& rectangle, std::string const& title)
{
    legend_.Set(rectangle, title);
}

void Profile::Draw()
{
//     histogram_.Draw("nostack");
    legend_.Draw();
}

void Profile::SetXAxis(std::string const& title, boca::Bounds<float> const& bounds)
{
    Draw();
    SetTitle(*profile_.GetXaxis(), title.c_str());
    if (bounds) profile_.GetXaxis()->SetLimits(bounds.Min(), bounds.Max());

}

void Profile::SetYAxis(std::string const& title, boca::Bounds<float> const& bounds)
{
    Draw();
    SetLog(bounds);
    SetTitle(*profile_.GetYaxis(), title.c_str());
    if (bounds) {
        profile_.GetYaxis()->SetLimits(bounds.Min(), bounds.Max());
        profile_.SetMinimum(bounds.Min());
        profile_.SetMaximum(bounds.Max());
    };

}

void Profile::SetDimensions(std::string const& name, int bins, Rectangle<float> const& bounds)
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
