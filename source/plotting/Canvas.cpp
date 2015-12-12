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

Canvas::Canvas(std::string const& path, std::string const& name, bool show_title)
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
    SetMargins(show_title);
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

void Canvas::SetMargins(bool show_title)
{
    canvas_.SetLeftMargin(2 * TextSize());
    if (show_title) canvas_.SetTopMargin(TextSize() * 1.5);
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

TCanvas const& Canvas::canvas() const
{
    return canvas_;
}

TCanvas& Canvas::canvas()
{
    return canvas_;
}
const std::string& Canvas::Title() const
{
    return title_;
}

}
