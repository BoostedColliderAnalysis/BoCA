/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TLegend.h"

#include "boca/generic/Flag.hh"
#include "boca/physics/Rectangle.hh"
#include "boca/Latex.hh"

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

    Legend(Latex const& title);

    Legend(boca::Rectangle<double> const& rectangle, Latex const& title = Latex());

    Legend(Orientation orientation, std::vector<Latex> const& entries, Latex const& title = Latex());

    void SetOrientation(Orientation orientation, std::vector<Latex> const& entries, Latex const& title);

    void Set(boca::Rectangle<double> const& rectangle, Latex const& title = Latex());

    void SetOrientation(Orientation orientation, Latex const& title);

    void Draw();

    void AddEntry(TObject const& object, Latex const& name);

    void AddEntry(TObject const& object, char const* name);

    void TwoColumn();

    boca::Rectangle<double> Rectangle();

private:

    double Width(std::vector<Latex> const& entries) const;

    double Height(std::vector<Latex> const& entries, Latex const& title) const;

    void SetCorners(boca::Rectangle<double> const& rectangle);

    void SetStyle();

    void SetTitle(Latex const& title);

    TLegend legend_;

    int columns_ = 1;
};

}
