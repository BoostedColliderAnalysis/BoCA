/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TH1F.h"
#include "THStack.h"
#include "TLine.h"

#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

namespace boca
{

class Histograms : public Canvas
{

public:

    Histograms();

    Histograms(std::string const& path, std::string const& name, bool show_title = false);

    ~Histograms();

    void Initialize(std::string const& path, std::string const& name, bool show_title = false);

    void AddHistogram(std::vector<double> const& values, std::string const& name, Rectangle<double> const& range);

    void AddHistogram(std::vector<double> const& values, std::string const& name, Range<double> const& range, bool is_int = false);

    void SetLegend(Orientation orientation, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Range<double> const& range = Range<double>());

    void SetYAxis(std::string const& title, Range<double> const& range = Range<double>());

    void AddLine(double x_value, std::string const& title = "");

private:

    Range<double> RangeY();

    Range<double> RangeX();

    void AddHistograms();

    THStack stack_;

    Legend legend_;

    std::vector<TH1F> histograms_;

    std::vector<TLine> lines_;

    Rectangle<double> range_;

};

}
