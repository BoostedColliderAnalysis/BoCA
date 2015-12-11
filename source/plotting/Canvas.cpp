#include "TPad.h"
#include "TStyle.h"
#include "plotting/Canvas.hh"
#include "plotting/Font.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace
{

std::string ExportFileSuffix()
{
    Info0;
    return ".pdf";
    return ".svg";
    return ".png";
}

}

Canvas::Canvas(std::string const& path, std::string const& name, bool has_title)
{
    Info0;
    path_ = path;
    title_ = name;
    gStyle->SetOptStat("");
    gStyle->SetTitleFont(FontCode(), "t");
    gStyle->SetTitleFontSize(TextSize());
    gPad->SetTickx();
    gPad->SetTicky();
    Fill();
    SetMargins(has_title);
}

std::string Canvas::FileName() const
{
    return path_ + "-" + title_ + ExportFileSuffix();
}

void Canvas::Fill()
{
    Info0;
    canvas_.SetFillColor(0);
    canvas_.SetFillStyle(0);
    gPad->SetFillColor(0);
    gPad->SetFillStyle(0);
    gPad->SetFrameFillColor(0);
    gPad->SetFrameFillStyle(0);
}

void Canvas::SetMargins(bool has_title)
{
    canvas_.SetLeftMargin(2 * TextSize());
    if (has_title) canvas_.SetTopMargin(TextSize() * 1.5);
    else canvas_.SetTopMargin(TextSize() / 4);
    canvas_.SetRightMargin(TextSize() / 3);
    canvas_.SetBottomMargin(2. * TextSize());
}

std::string Canvas::SaveAs(std::string const& name)
{
    Info0;
    canvas_.SaveAs(name.c_str());
    return name;
}

void Canvas::SetLog(float min, float max)
{
    Info0;
    if (min > 0 && min / max < 0.1) canvas_.SetLogy();
}

void Canvas::SetLog(Limits const& limits)
{
    Info0;
    if (limits && limits.Min() > 0 && limits.Min() / limits.Max() < 0.1) canvas_.SetLogy();
}

TCanvas const& Canvas::canvas() const
{
    return canvas_;
}

TCanvas& Canvas::canvas()
{
    return canvas_;
}
const std::__cxx11::string& Canvas::Title() const
{
    return title_;
}

}
