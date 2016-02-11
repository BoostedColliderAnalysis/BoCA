/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TProfile2D.h"

#include "physics/Rectangle.hh"
#include "plotting/Plot.hh"
#include "plotting/Canvas.hh"

namespace boca
{

class Profile : public Canvas
{

public:

    Profile(std::string const& path, std::string const& folder, std::string const& name, bool show_title = false);

    ~Profile();

    void SetXAxis(std::string const& title);

    void SetYAxis(std::string const& title);

    void SetZAxis(std::string const& title, int bins);

    void SetProfile(Plot const& signal, Plot const& background);

    void SetDimensions(std::string const& name, int bins, Rectangle<float> const& range);

    std::string FileBaseName() const override;

private:

    void SetDimensions(int x_bins, int y_bins, Rectangle<float> const& range);

    void Draw();

    TProfile2D profile_;

    Range<float> range_;

    Rectangle<float> rectangle_;

};

}
