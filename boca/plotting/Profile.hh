/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TProfile2D.h"

#include "boca/math/Rectangle.hh"
#include "boca/plotting/Plot.hh"
#include "boca/plotting/Canvas.hh"

namespace boca
{

class Profile : public Canvas
{

public:

    Profile(std::string const& path, std::string const& folder, std::string const& name, bool show_title = false);

    ~Profile();

    void SetXAxis(latex::String const& title);

    void SetYAxis(latex::String const& title);

    void SetZAxis(latex::String const& title, int bins);

    void SetProfile(Plot const& signal, Plot const& background);

    void SetDimensions(latex::String const& name, int bins, Rectangle<double> const& range);

    std::string FileBaseName() const override;

private:

    void SetDimensions(int x_bins, int y_bins, Rectangle<double> const& range);

    void Draw();

    TProfile2D profile_;

    Range<double> range_;

    Rectangle<double> rectangle_;

};

}
