#pragma once

#include "TProfile.h"

#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

class Plot2;
// class EColor;

namespace boca
{

class Profile : public Canvas
{

public:

    Profile(std::string const& path, std::string const& name, bool show_title = false);

    ~Profile();

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetLegend(Vector2<float> const& point, float width, float height, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Limits<float> const& limits = Limits<float>());

    void SetYAxis(std::string const& title, Limits<float> const& limits = Limits<float>());

    void SetProfile(Plot const& signal, Plot const& background);

    void SetDimensions(std::string const& name, int bins, Vector2<float> const& min, Vector2<float> const& max);

    boca::Legend & Legend();

private:

    boca::Legend legend_;

    TProfile profile_;

};

}
