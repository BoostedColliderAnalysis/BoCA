/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TAxis.h"
#include "TAttText.h"
#include "TAttLine.h"
// #include "boca/plotting/Style.hh"
#include "boca/plotting/Font.hh"
#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

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

void SetAxis(TAxis& axis, std::string const& title)
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
    auto bins = axis.GetNbins();
    auto min = axis.GetXmin();
    auto width = (axis.GetXmax() - min) / bins;
    axis.Set(bins, Transform(IntegerRange(bins), [=](int bin) {
        return std::pow(10., min + bin * width);
    }).data());
}

}

