#pragma once

#include <string>

class TAttText;
class TAttLine;
class TAxis;

namespace boca
{

void SetTextStyle(TAttText& text);

void SetPlotStyle(TAttLine& line, int index);

void SetAxis(TAxis& axis, std::string const& title);

}
