/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TH2F.h"
#include "TExec.h"

#include "plotting/Plot.hh"
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

    void SetXAxis(std::string const& title);

    void SetYAxis(std::string const& title);

    void AddHistogram(std::string const& name, int bins, Rectangle<double> const& range, Plot const& points, EColor color);

    std::string FileBaseName() const override;

private:

    boca::Legend & Legend();

    void Draw();

    TExec Exec(EColor color);

    boca::Legend legend_;

    std::vector<TH2F> histograms_;

    std::vector<TExec> execs_;


};

}
