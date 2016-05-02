/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TH1F.h"
#include "THStack.h"
#include "TLine.h"

#include "boca/plotting/Canvas.hh"
#include "boca/plotting/Legend.hh"
#include "boca/Names.hh"

namespace boca
{

class Histograms : public Canvas
{

public:

    Histograms();

    Histograms(std::string const& path, std::string const& name, bool show_title = false);

    ~Histograms();

    void AddHistogram(const std::vector< double >& values, const Names& name, const boca::Rectangle< double >& range);

    void AddHistogram(const std::vector< double >& values, const Names& name, const boca::Range< double >& range, bool is_int = false);

    void SetLegend(Orientation orientation, std::string const& title = "");

    void Draw();

    void SetXAxis(Latex const& title, Range<double> const& range = Range<double>());

    void SetYAxis(Latex const& title, Range<double> const& range = Range<double>());

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
