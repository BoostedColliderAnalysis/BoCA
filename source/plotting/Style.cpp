/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TAxis.h"
#include "TAttText.h"
#include "TAttLine.h"
#include "plotting/Style.hh"
#include "plotting/Font.hh"
#include "Types.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace
{

void SetAxis(TAttAxis& axis)
{
    INFO0;
    axis.SetTitleFont(FontCode());
    axis.SetTitleSize(TextHeight());
    axis.SetLabelFont(FontCode());
    axis.SetLabelSize(LabelHeight());
}

}

void SetTitle(TAxis& axis, std::string const& title)
{
    INFO0;
    axis.SetTitle(title.c_str());
    axis.CenterTitle();
    SetAxis(axis);
}

void SetText(TAttText& text)
{
    INFO0;
    text.SetTextFont(FontCode());
    text.SetTextSize(TextHeight());
}

void SetLine(TAttLine& line, int index)
{
    INFO0;
    line.SetLineColor(ColorCode(index));
    line.SetLineStyle(index + 1);
}
void SetLogarithmic(TAxis& axis)
{
    INFO0;
    int bins = axis.GetNbins();
    float min = axis.GetXmin();
    float max = axis.GetXmax();
    float width = (max - min) / bins;
    std::vector<double> new_bins;
//     for (int bin = 0; bin <= bins; ++bin) new_bins.emplace_back(std::pow(10., min + bin * width));
    for (auto const& bin : Range(bins)) new_bins.emplace_back(std::pow(10., min + bin * width));
    axis.Set(bins, &new_bins.front());
}

}
