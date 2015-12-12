/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>

#include "TLegend.h"

#include "Flag.hh"

namespace boca
{

class Point;

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

    Legend(Point const& min, float width, float height, std::string const& title = "");

    Legend(Orientation orientation, std::vector<std::string> const& entries, std::string const& title = "");

    void SetOrientation(Orientation orientation, std::vector<std::string> const& entries, std::string const& title);

    void Set(Point const& min, float width, float height, std::string const& title = "");

    void SetOrientation(Orientation orientation, std::string const& title);

    void Draw();

    void AddEntry(TObject const& object, std::string const& name);

    void TwoColumn();

private:

    void SetCorners(Point const& min, float width, float height);

    void SetStyle();

    void SetTitle(std::string const& title);

    TLegend legend_;
};

}
