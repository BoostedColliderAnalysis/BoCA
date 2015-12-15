/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TH2F.h"
#include "TExec.h"

#include "physics/Vector3.hh"
#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

namespace boca
{

class Histogram2Dim : public Canvas
{

public:

    Histogram2Dim(std::string const& path, std::string const& name, bool show_title = false);

    ~Histogram2Dim();

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetLegend(Rectangle<float> const& rectangle, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void SetYAxis(std::string const& title, Bounds<float> const& bounds = Bounds<float>());

    void AddHistogram(std::string const& name, int bins, Rectangle<float> const& bounds, std::vector<Vector3<float>> const& points, EColor color);

    boca::Legend & Legend();

private:

    void SetExec(EColor color);

    boca::Legend legend_;

    std::vector<TH2F> histograms_;

    std::vector<TExec> execs_;


};

}
