/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>
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
    normal = 1 << 0,
    bold = 1 << 1,
    italic = 1 << 2
};

template<>
struct Flag<Style> {
    static const bool enable = true;
};

float TextHeight();

float LabelHeight();

int ColorCode(int number);

std::string Formula(std::string const& text, Font font = Font::times);

int FontCode(Font font = Font::times, Style style = Style::normal);

}
