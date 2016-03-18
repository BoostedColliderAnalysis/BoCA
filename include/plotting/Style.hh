/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

class TAttText;
class TAttLine;
class TAxis;

namespace boca
{

void SetText(TAttText& text);

void SetLine(TAttLine& line, int index);

void SetTitle(TAxis& axis, std::string const& title);

void SetLogarithmic(TAxis& axis);

}

