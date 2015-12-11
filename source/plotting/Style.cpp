
#include "TAxis.h"
#include "TAttText.h"
#include "TAttLine.h"
#include "TAttAxis.h"
#include "plotting/Style.hh"
#include "plotting/Font.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace
{

void SetAxis(TAttAxis& axis)
{
    Info0;
    axis.SetTitleFont(FontCode());
    axis.SetTitleSize(TextSize());
    axis.SetLabelFont(FontCode());
    axis.SetLabelSize(LabelSize());
}

}

void SetAxis(TAxis& axis, std::string const& title)
{
    Info0;
    axis.SetTitle(title.c_str());
    axis.CenterTitle();
    SetAxis(axis);
}

void SetTextStyle(TAttText& text)
{
    Info0;
    text.SetTextFont(FontCode());
    text.SetTextSize(TextSize());
}

void SetPlotStyle(TAttLine& line, int index)
{
    Info0;
    line.SetLineColor(ColorCode(index));
    line.SetLineStyle(index + 1);
}

}
