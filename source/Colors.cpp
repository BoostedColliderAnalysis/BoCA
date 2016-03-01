/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TColor.h"
#include "TStyle.h"

#include "Colors.hh"
#include "Debug.hh"

namespace boca
{

Color::Color()
{
    Initialize();
    SetPalette();
}

void Color::Initialize()
{
    if (Palette().size() > 0) return;
    CHECK(Length().size() == red().size(), red().size());
    CHECK(Length().size() == green().size(), green().size());
    CHECK(Length().size() == blue().size(), blue().size());
    Palette().reserve(50);
    int color_table = TColor::CreateGradientColorTable(Length().size(), &Length().front(), &red().front(), &green().front(), &blue().front(), Palette().size());
    for (auto & color : Palette()) color = color_table + (&color - &Palette().front());
}

void Color::SetPalette()
{
    gStyle->SetPalette(Palette().size(), &Palette().front());
}

std::vector< double > Color::red() const
{
    return { 1, 0};
}

std::vector< double > Color::green() const
{
    return { 1, 0};
}

std::vector< double > Color::blue() const
{
    return { 1, 0};
}

std::vector< double > Color::Length() const
{
    return { 0, 1};
}

std::vector<int> Red::palette_;

std::vector< int >& Red::Palette()
{
    return palette_;
}

std::vector< double > Red::red() const
{
    return { 1, 1};
}

std::string Red::Action()
{
    return "boca::Red();";
}

std::vector<int> Blue::palette_;

std::vector< int >& Blue::Palette()
{
    return palette_;
}

std::vector< double > Blue::blue() const
{
    return { 1, 1};
}

std::string Blue::Action()
{
    return "boca::Blue();";
}

std::vector<int> Heat::palette_;

std::vector< int >& Heat::Palette()
{
    return palette_;
}

std::vector< double > Heat::red() const
{
    return { 0., 0., 0.87, 1., 0.51 };
}

std::vector< double > Heat::green() const
{
    return { 0., 0.81, 1., 0.2, 0. };
}

std::vector< double > Heat::blue() const
{
    return { 0.51, 1., 0.12, 0., 0. };
}

std::vector< double > Heat::Length() const
{
    return { 0., 0.34, 0.61, 0.84, 1. };
}

std::string Heat::Action()
{
    return "boca::Heat();";
}

// namespace
// {
//
// std::vector<int> Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue)
// {
//     std::vector<int> colors(50);
//     int color_table = TColor::CreateGradientColorTable(length.size(), &length.front(), &red.front(), &green.front(), &blue.front(), colors.size());
//     for (auto & color : colors) color = color_table + (&color - &colors.front());
//     return colors;
// }
//
// void Colors(bool& initialized, std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue, std::vector<int>& colors)
// {
//     if (!initialized) {
//         colors = Table(length, red, green, blue);
//         initialized = true;
//     }
//     gStyle->SetPalette(colors.size(), &colors.front());
// }
//
// }
//
// void Color::Red()
// {
//     std::vector<double> red = { 1, 1};
//     std::vector<double> green = { 1, 0};
//     std::vector<double> blue = { 1, 0};
//     std::vector<double> length = { 0, 1};
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }
//
// void Color::Blue()
// {
//     std::vector<double> red = { 1, 0};
//     std::vector<double> green = { 1, 0};
//     std::vector<double> blue = { 1, 1};
//     std::vector<double> length = { 0, 1};
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }
//
// void Color::Heat()
// {
//     std::vector<double> length = { 0., 0.34, 0.61, 0.84, 1. };
//     std::vector<double> red = { 0., 0., 0.87, 1., 0.51 };
//     std::vector<double> green = { 0., 0.81, 1., 0.2, 0. };
//     std::vector<double> blue = { 0.51, 1., 0.12, 0., 0. };
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }

}
