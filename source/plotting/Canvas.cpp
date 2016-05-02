/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TPad.h"
#include "TStyle.h"

#include "boca/plotting/Canvas.hh"
#include "boca/plotting/Font.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

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

Canvas::Canvas()
{
    INFO0;
    Initialize();
}

Canvas::Canvas(std::string const& path, std::string const& name, bool show_title)
{
    INFO0;
    path_ = path;
    title_ = name;
    SetMargins(show_title);
    Initialize();
}

void Canvas::Initialize()
{
    INFO0;
    gStyle->SetOptStat("");
    gStyle->SetTitleFont(FontCode(), "t");
    gStyle->SetTitleFontSize(TextHeight());
    gPad->SetTickx();
    gPad->SetTicky();
    canvas_.SetFillColor(0);
    canvas_.SetFillStyle(0);
    gPad->SetFillColor(0);
    gPad->SetFillStyle(0);
    gPad->SetFrameFillColor(0);
    gPad->SetFrameFillStyle(0);
}

std::string Canvas::FileName() const
{
    INFO0;
    return FileBaseName() + ExportFileSuffix();
}

std::string Canvas::FileBaseName() const
{
    INFO0;
    return path_ + "-" + title_ ;
}

std::string Canvas::Path() const
{
    return path_;
}

void Canvas::SetMargins(bool show_title)
{
    INFO0;
    canvas_.SetLeftMargin(TextHeight() * 2);
    canvas_.SetTopMargin(TextHeight() * (show_title ? 1.5 : 1));
    canvas_.SetRightMargin(TextHeight() * 1.1);
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
    INFO0;
    return canvas_;
}

TCanvas& Canvas::canvas()
{
    INFO0;
    return canvas_;
}

std::string const& Canvas::Title() const
{
    INFO0;
    return title_;
}

void Canvas::SetLog()
{
    INFO0;
    canvas_.SetLogy();
}

}
