#pragma once

#include "TProfile.h"

#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

namespace boca
{

class Profile : public Canvas
{

public:

    Profile(std::string const& path, std::string const& name, bool show_title = false);

    ~Profile();

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetLegend(Rectangle<float> const& rectangle, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void SetYAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void SetProfile(Plot const& signal, Plot const& background);

    void SetDimensions(std::string const& name, int bins, Rectangle<float> const& bounds);

    boca::Legend & Legend();

private:

    boca::Legend legend_;

    TProfile profile_;

};

}
