#pragma once

#include <string>

class TAttText;
class TAttLine;
class TAxis;

namespace boca
{

void SetStyle(TAttText& text);

void SetStyle(TAttLine& line, int index);

void SetTitle(TAxis& axis, std::string const& title);

}
