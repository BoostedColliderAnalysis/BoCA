/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <sys/stat.h>
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
    INFO0;
    return ".pdf";
    return ".svg";
    return ".png";
}

}

Canvas::Canvas(std::string const& path, std::string const& name, bool show_title)
{
    INFO0;
//     mkdir(path.c_str(), 0700);
    path_ = path;
    title_ = name;
    gStyle->SetOptStat("");
    gStyle->SetTitleFont(FontCode(), "t");
    gStyle->SetTitleFontSize(TextHeight());
    gPad->SetTickx();
    gPad->SetTicky();
    Fill();
    SetMargins(show_title);
}

std::string Canvas::FileName() const
{
    return FileBaseName() + ExportFileSuffix();
}

std::string Canvas::FileBaseName() const
{
    return path_ + "-" + title_ ;
}

std::string Canvas::Path() const
{
    return path_;
}

void Canvas::Fill()
{
    INFO0;
    canvas_.SetFillColor(0);
    canvas_.SetFillStyle(0);
    gPad->SetFillColor(0);
    gPad->SetFillStyle(0);
    gPad->SetFrameFillColor(0);
    gPad->SetFrameFillStyle(0);
}

void Canvas::SetMargins(bool show_title)
{
    canvas_.SetLeftMargin(2 * TextHeight());
    if (show_title) canvas_.SetTopMargin(TextHeight() * 1.5);
    else canvas_.SetTopMargin(TextHeight() / 3);
    canvas_.SetRightMargin(TextHeight() / 3);
    canvas_.SetBottomMargin(2.1 * TextHeight());
}

std::string Canvas::SaveAs(std::string const& name)
{
    INFO0;
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
std::string const& Canvas::Title() const
{
    return title_;
}
void Canvas::SetLog()
{
    canvas_.SetLogy();
}

}
