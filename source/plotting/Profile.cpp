/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <sys/stat.h>
// #include <cmath>

#include "plotting/Style.hh"
#include "plotting/Profile.hh"
#include "plotting/Font.hh"

#include "Branches.hh"
#include "Types.hh"

// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Profile::Profile(std::string const& path, std::string const& folder, std::string const& name, bool show_title):
    Canvas(path, folder + "-" + name, show_title)
{
    INFO(path);
    mkdir(path.c_str(), 0700);
    canvas().SetRightMargin(TextHeight() * 2.8);
}

Profile::~Profile()
{
    Info0;
    Draw();
    SaveAs(FileName());
}

void Profile::Draw()
{
    Info0;
    Color().Heat();
    profile_.Draw("colz");
}

void Profile::SetXAxis(std::string const& title)
{
    INFO(title);
    SetTitle(*profile_.GetXaxis(), title);
}

void Profile::SetYAxis(std::string const& title)
{
    INFO(title);
    SetTitle(*profile_.GetYaxis(), title);
}

void Profile::SetZAxis(const std::string& title, int bins)
{
    SetTitle(*profile_.GetZaxis(), title);
    profile_.SetMinimum(bounds_.Min());
    profile_.SetMaximum(bounds_.Max());
    profile_.SetContour(bins);
}

void Profile::SetDimensions(std::string const& name, int bins, Rectangle<float> const& bounds)
{
    INFO(name);

    rectangle_ = bounds;
    SetLog(bounds);
    if (canvas().GetLogx()) rectangle_.Horizontal().Log();
    if (canvas().GetLogy()) rectangle_.Vertical().Log();
    SetDimensions(bins, bins, rectangle_);

    profile_.SetName(name.c_str());
}

void Profile::SetDimensions(int bin_x, int bin_y, Rectangle<float> const& bounds)
{
    Info0;
    profile_.SetBins(bin_x, bounds.XMin(), bounds.XMax(), bin_y, bounds.YMin(), bounds.YMax());
}

void Profile::SetProfile(Plot const& signal, Plot const& background)
{
    Info0;
    if (signal.x_is_int) SetDimensions(std::floor(rectangle_.Width()), profile_.GetNbinsY(), rectangle_);
    if (signal.y_is_int) SetDimensions(profile_.GetNbinsX(), std::floor(rectangle_.Height()), rectangle_);
    if (canvas().GetLogx()) SetLogarithmic(*profile_.GetXaxis());
    if (canvas().GetLogy()) SetLogarithmic(*profile_.GetYaxis());
    for (auto const & point : signal.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    for (auto const & point : background.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    auto minmax = std::minmax_element(signal.Data().begin(), signal.Data().end(), [](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Z() < b.Z();
    });
    bounds_.Set(minmax.first->Z(), minmax.second->Z());
}
std::string Profile::FileBaseName() const
{
    return Path() + "/" + Title() ;
}

}
