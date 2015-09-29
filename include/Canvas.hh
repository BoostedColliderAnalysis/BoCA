#pragma once

#include <string>
#include "TCanvas.h"
#include "Flag.hh"

namespace boca
{

enum class Font
{
    times,
    helvetica,
    courier,
    symbol
};

enum class Style
{
    normal = 0,
    bold = 1 << 0,
    italic = 1 << 1
};

template<>
struct Flag<Style> {
    static const bool enable = true;
};

enum class Precision
{
    low = 0,
    normal = 1,
    high = 2,
    pixel = 3
};


class Canvas{

public:

  Canvas();

TCanvas &canvas();

static void SetTextStyle(TAttText & text);

void SetLog(float min=0.001, float max=1);

static void SetPlotStyle(TAttLine& line, int index);

static void SetAxis(TAxis& axis, std::string const& title);

std::string SaveAs(std::string const& name);

private:

/**
 * @brief Make plot backgrounds transparent
 *
 */
void Fill(TAttFill& pad) const;

std::string ExportFileSuffix() const;

static float TextSize();

static float LabelSize();

static int ColorCode(int number);

std::string Formula(std::string const& text);

static int FontCode(Font font = Font::times, Style style = Style::normal);

static int FontNumber(Font font = Font::times, Style style = Style::normal);

static int Precision();

TCanvas canvas_;

};

}
