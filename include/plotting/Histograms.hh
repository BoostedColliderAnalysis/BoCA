/**
 * Copyright (C) 2015 Jan Hajer
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

    Histograms(std::string const& path, std::string const& name, bool show_title = false);

    ~Histograms();

    void AddHistogram(std::vector<float> const& values, std::string const& name, Rectangle<float>& bounds);

    void SetLegend(Orientation orientation, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void SetYAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void AddLine(float x_value);

private:

    Bounds<double> LimitsY();

    Bounds<double> LimitsX();

    void AddHistograms();

    THStack stack_;

    Legend legend_;

    std::vector<TH1F> histograms_;

    std::vector<TLine> lines_;

};

}
