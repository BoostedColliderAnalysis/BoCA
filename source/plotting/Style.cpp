/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TAxis.h"
#include "TAttText.h"
#include "TAttLine.h"
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
    axis.SetTitleSize(TextHeight());
    axis.SetLabelFont(FontCode());
    axis.SetLabelSize(LabelHeight());
}

}

void SetTitle(TAxis& axis, std::string const& title)
{
    Info0;
    axis.SetTitle(title.c_str());
    axis.CenterTitle();
    SetAxis(axis);
}

void SetText(TAttText& text)
{
    Info0;
    text.SetTextFont(FontCode());
    text.SetTextSize(TextHeight());
}

void SetLine(TAttLine& line, int index)
{
    Info0;
    line.SetLineColor(ColorCode(index));
    line.SetLineStyle(index + 1);
}

}
