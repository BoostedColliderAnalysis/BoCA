/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <sys/stat.h>

#include "boca/plotting/Style.hh"
#include "boca/plotting/Profile.hh"
#include "boca/plotting/Font.hh"

#include "boca/Colors.hh"
#include "boca/generic/Types.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

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
    INFO0;
    Draw();
    SaveAs(FileName());
}

void Profile::Draw()
{
    INFO0;
    Heat();
    profile_.Draw("colz");
}

void Profile::SetXAxis(Latex const& title)
{
    INFO(title.str(Medium::root));
    SetAxis(*profile_.GetXaxis(), title);
}

void Profile::SetYAxis(Latex const& title)
{
    INFO(title.str(Medium::root));
    SetAxis(*profile_.GetYaxis(), title);
}

void Profile::SetZAxis(const Latex& title, int bins)
{
    SetAxis(*profile_.GetZaxis(), title);
    profile_.SetMinimum(range_.Min());
    profile_.SetMaximum(range_.Max());
    profile_.SetContour(bins);
}

void Profile::SetDimensions(Latex const& name, int bins, Rectangle<double> const& range)
{
    INFO(name.str(Medium::root));

    rectangle_ = range;
    SetLog(range.Vertical());
    if (canvas().GetLogx()) rectangle_.Horizontal().Log();
    if (canvas().GetLogy()) rectangle_.Vertical().Log();
    SetDimensions(bins, bins, rectangle_);

    profile_.SetName(name.str(Medium::root).c_str());
}

void Profile::SetDimensions(int bin_x, int bin_y, Rectangle<double> const& range)
{
    INFO0;
    profile_.SetBins(bin_x, range.XMin(), range.XMax(), bin_y, range.YMin(), range.YMax());
}

void Profile::SetProfile(Plot const& signal, Plot const& background)
{
    INFO0;
    if (signal.x_is_int) SetDimensions(std::floor(rectangle_.Width()), profile_.GetNbinsY(), rectangle_);
    if (signal.y_is_int) SetDimensions(profile_.GetNbinsX(), std::floor(rectangle_.Height()), rectangle_);
    if (canvas().GetLogx()) SetLogarithmic(*profile_.GetXaxis());
    if (canvas().GetLogy()) SetLogarithmic(*profile_.GetYaxis());
    for (auto const & point : signal.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    for (auto const & point : background.Data()) profile_.Fill(point.X(), point.Y(), point.Z());
    auto minmax = std::minmax_element(signal.Data().begin(), signal.Data().end(), [](Vector3<double> const & a, Vector3<double> const & b) {
        return a.Z() < b.Z();
    });
    range_.Set(minmax.first->Z(), minmax.second->Z());
}
std::string Profile::FileBaseName() const
{
    return Path() + "/" + Title() ;
}

}
