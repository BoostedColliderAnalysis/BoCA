/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TLegend.h"

#include "Flag.hh"
#include "physics/Rectangle.hh"

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
    center = 1 << 0,
    left = 1 << 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
    inside = 1 << 5,
    outside = 1 << 6
};

template<>
struct Flag<Orientation> {
    static const bool enable = true;
};

class Legend
{
public:

    Legend();

    Legend(std::string const& title);

    Legend(boca::Rectangle<float> const& rectangle, std::string const& title = "");

    Legend(Orientation orientation, std::vector<std::string> const& entries, std::string const& title = "");

    void SetOrientation(Orientation orientation, std::vector<std::string> const& entries, std::string const& title);

    void Set(boca::Rectangle<float> const& rectangle, std::string const& title = "");

    void SetOrientation(Orientation orientation, std::string const& title);

    void Draw();

    void AddEntry(TObject const& object, std::string const& name);

    void TwoColumn();

private:

    void SetCorners(boca::Rectangle<float> const& rectangle);

    void SetStyle();

    void SetTitle(std::string const& title);

    boca::Rectangle<double> Rectangle();

    TLegend legend_;
};

}
