#include "Rtypes.h"
#include "plotting/Font.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace
{

enum class Precision
{
    low = 0,
    normal = 1,
    high = 2,
    pixel = 3
};

int Precision()
{
    Info0;
    return 2;
}

int FontNumber(Font font, Style style)
{
    Info0;
    switch (font) {
    case Font::times:
        if (style == Style::italic) return 1;
        if (style == Style::bold) return 2;
        if (style == (Style::italic | Style::bold)) return 3;
        return 13;
    case Font::helvetica:
        if (style == Style::italic) return 5;
        if (style == Style::bold) return 6;
        if (style == (Style::italic | Style::bold)) return 7;
        return 4;
    case Font::courier:
        if (style == Style::italic) return 9;
        if (style == Style::bold) return 10;
        if (style == (Style::italic | Style::bold)) return 11;
        else return 8;
    case Font::symbol:
        if (style == Style::italic) return 15;
        if (style == Style::bold) return 14;
        if (style == (Style::italic | Style::bold)) return 14;
        return 12;
    default :
        return 13;
    }
}

}

float TextSize()
{
    Info0;
    switch (Precision()) {
    case 2 : return 0.07;
    case 3 : return 20;
    default : return 0.0;
    }
}

float LabelSize()
{
    Info0;
    switch (Precision()) {
    case 2 : return 0.05;
    case 3 : return 15;
    default : return 0.04;
    }
}

int ColorCode(int number)
{
    Info0;
    switch (number) {
    case 0 : return kBlack;
    case 1 : return kRed;
    case 2 : return kBlue;
    case 3 : return kTeal - 5;
    case 4 : return kPink + 1;
    case 5 : return kViolet;
    case 6 : return kOrange;
    case 7 : return kGreen + 3;
    case 8 : return kCyan - 3;
    case 9 : return kMagenta - 3;
    case 10 : return kAzure;
    case 11 : return kYellow - 9;
    case 12 : return kSpring - 5;
    case 13 : return kGray;
    default : return kBlack;
    }
}

std::string Formula(std::string const& text, Font font)
{
    INFO(text);
    return "#font[" + std::to_string(FontCode(font, Style::italic)) + "]{" + text + "}";
}

int FontCode(Font font, Style style)
{
    Info0;
    return 10 * FontNumber(font, style) + Precision();
}

}
