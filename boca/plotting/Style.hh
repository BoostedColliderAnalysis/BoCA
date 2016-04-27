/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Latex.hh"

class TAttText;
class TAttLine;
class TAxis;

namespace boca
{

void SetText(TAttText& text);

void SetLine(TAttLine& line, int index);

void SetAxis(TAxis& axis, Latex const& title);

void SetLogarithmic(TAxis& axis);

}

