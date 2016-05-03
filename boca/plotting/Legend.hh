/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TLegend.h"

#include "boca/generic/Flag.hh"
#include "boca/physics/Rectangle.hh"
#include "boca/latex/String.hh"

namespace boca
{

/**
 * @brief Orientation of the Legend
 *
 * the default position is inside center center
 * only deviations from this position need to be requested
 *
 */
enum class Orientation
{
    none = 0,
    center = 1 << 0,
    left = 1 << 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
    outside = 1 << 5
//     inside = 1 << 6,
};

template<>
struct Flag<Orientation> {
    static const bool enable = true;
};

std::string Name(Orientation orientation);

class Legend
{
public:

    Legend();

    Legend(latex::String const& title);

    Legend(boca::Rectangle<double> const& rectangle, latex::String const& title = latex::String());

    Legend(Orientation orientation, std::vector<latex::String> const& entries, latex::String const& title = latex::String());

    void SetOrientation(Orientation orientation, std::vector<latex::String> const& entries, latex::String const& title);

    void Set(boca::Rectangle<double> const& rectangle, latex::String const& title = latex::String());

    void SetOrientation(Orientation orientation, latex::String const& title);

    void Draw();

    void AddEntry(TObject const& object, latex::String const& name);

    void AddEntry(TObject const& object, char const* name);

    void TwoColumn();

    boca::Rectangle<double> Rectangle();

private:

    double Width(std::vector<latex::String> const& entries) const;

    double Height(std::vector<latex::String> const& entries, latex::String const& title) const;

    void SetCorners(boca::Rectangle<double> const& rectangle);

    void SetStyle();

    void SetTitle(latex::String const& title);

    TLegend legend_;

    int columns_ = 1;
};

}
