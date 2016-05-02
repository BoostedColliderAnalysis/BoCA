/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Flag.hh"

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
    none = 0,
    normal = 1 << 0,
    bold = 1 << 1,
    italic = 1 << 2
};

template<>
struct Flag<Style> {
    static const bool enable = true;
};

double TextHeight();

double LabelHeight();

int ColorCode(int number);

int FontCode(Style style = Style::normal);

}
