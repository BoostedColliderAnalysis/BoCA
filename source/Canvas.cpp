#include "TPad.h"
#include "TStyle.h"
#include "Canvas.hh"
#include "Font.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Canvas::Canvas()
{
    Info0;
    gStyle->SetOptStat("");
    gStyle->SetTitleFont(FontCode(), "t");
    gStyle->SetTitleFontSize(TextSize());
    //     canvas_.cd();
    gPad->SetTickx();
    gPad->SetTicky();
    Fill();
    SetMargin();
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

void Canvas::SetMargin(){
  canvas_.SetLeftMargin(2 * TextSize());
  canvas_.SetTopMargin(TextSize() / 4);
  canvas_.SetRightMargin(TextSize() / 3);
  canvas_.SetBottomMargin(2. * TextSize());
}

std::string Canvas::SaveAs(std::string const& name)
{
    Info0;
    canvas_.SaveAs((name + ExportFileSuffix()).c_str());
    return name;
}

void Canvas::SetLog(float min, float max)
{
    Info0;
    if (min > 0 && min / max < 0.1) canvas_.SetLogy();
}

std::string Canvas::ExportFileSuffix() const
{
    Info0;
    return ".pdf";
    return ".svg";
    return ".png";
}

TCanvas& Canvas::canvas()
{
    return canvas_;
}

}
