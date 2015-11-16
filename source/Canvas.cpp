#include "Canvas.hh"
#include "Rtypes.h"
#include "TPad.h"
#include "TStyle.h"
#include "TAxis.h"
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
    Fill();
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
    return ".svg";
    return ".png";
    return ".pdf";
}

void Canvas::SetAxis(TAxis& axis, std::string const& title)
{
    Info0;
    axis.SetTitle(title.c_str());
    axis.CenterTitle();
    axis.SetTitleFont(FontCode());
    axis.SetTitleSize(TextSize());
    axis.SetLabelFont(FontCode());
    axis.SetLabelSize(LabelSize());
}

void Canvas::SetTextStyle(TAttText& text)
{
    Info0;
    text.SetTextFont(FontCode());
    text.SetTextSize(TextSize());
}


float Canvas::TextSize()
{
    Info0;
    switch (Precision()) {
    case 2 : return 0.05;
    case 3 : return 20;
    default : return 0.05;
    }
}

float Canvas::LabelSize()
{
    Info0;
    switch (Precision()) {
    case 2 : return 0.04;
    case 3 : return 15;
    default : return 0.04;
    }
}

int Canvas::ColorCode(int number)
{
    Info0;
    switch (number) {
    case 0 : return kBlack;
    case 1 : return kRed;
    case 2 : return kBlue;
    case 3 : return kTeal - 5;
    case 4 : return kPink + 1;
    case 5 : return kViolet;
    case 6 : return kOrange;
    case 7 : return kGreen + 3;
    case 8 : return kCyan - 3;
    case 9 : return kMagenta - 3;
    case 10 : return kAzure;
    case 11 : return kYellow - 9;
    case 12 : return kSpring - 5;
    case 13 : return kGray;
    default : return kBlack;
    }
}

void Canvas::SetPlotStyle(TAttLine& line, int index)
{
    Info0;
    line.SetLineColor(ColorCode(index));
    line.SetLineStyle(index + 1);
}

int Canvas::Precision()
{
    Info0;
    return 2;
}

std::string Canvas::Formula(std::string const& text)
{
    Info(text);
    return "#font[" + std::to_string(FontCode(Font::times, Style::italic)) + "]{" + text + "}";
}

int Canvas::FontCode(Font font, Style style)
{
    Info0;
    return 10 * FontNumber(font, style) + Precision();
}

int Canvas::FontNumber(Font font, Style style)
{
    Info0;
    switch (font) {
    case Font::times:
        if (style == Style::italic) return 1;
        if (style == Style::bold) return 2;
        if (style == (Style::italic | Style::bold)) return 3;
        return 13;
    case Font::helvetica:
        if (style == Style::italic) return 5;
        if (style == Style::bold) return 6;
        if (style == (Style::italic | Style::bold)) return 7;
        return 4;
    case Font::courier:
        if (style == Style::italic) return 9;
        if (style == Style::bold) return 10;
        if (style == (Style::italic | Style::bold)) return 11;
        else return 8;
    case Font::symbol:
        if (style == Style::italic) return 15;
        if (style == Style::bold) return 14;
        if (style == (Style::italic | Style::bold)) return 14;
        return 12;
    default :
        return 13;
    }
}

TCanvas& Canvas::canvas()
{
    return canvas_;
}

}
