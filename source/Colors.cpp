/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TColor.h"
#include "TStyle.h"
#include "boca/generic/Vector.hh"

#include "boca/Colors.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Color::Color()
{
    Initialize();
    SetPalette();
}

void Color::Initialize()
{
    if (!Palette().empty()) return;
    CHECK(Length().size() == red().size(), red().size());
    CHECK(Length().size() == green().size(), green().size());
    CHECK(Length().size() == blue().size(), blue().size());
    Palette().reserve(50);
    auto color_table = TColor::CreateGradientColorTable(Length().size(), Length().data(), red().data(), green().data(), blue().data(), Palette().size());
    for (auto & color : Palette()) color = color_table + Position(Palette(), color);
}

void Color::SetPalette()
{
    gStyle->SetPalette(Palette().size(), Palette().data());
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

}
