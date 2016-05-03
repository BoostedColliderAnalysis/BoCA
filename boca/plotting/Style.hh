/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/latex/String.hh"

class TAttText;
class TAttLine;
class TAxis;

namespace boca
{

void SetText(TAttText& text);

void SetLine(TAttLine& line, int index);

void SetAxis(TAxis& axis, latex::String const& title);

void SetLogarithmic(TAxis& axis);

}

