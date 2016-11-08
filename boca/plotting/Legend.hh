/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TLegend.h"

#include "boca/math/Rectangle.hh"
#include "boca/latex/String.hh"
#include "boca/plotting/Orientation.hh"

namespace boca
{

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
