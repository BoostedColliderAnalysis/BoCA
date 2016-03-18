/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLine.h"

#include "plotting/Legend.hh"
#include "plotting/Canvas.hh"

namespace boca
{

class Graphs : public Canvas
{

public:

    Graphs(std::string const& path, std::string const& name, bool show_title = false);

    ~Graphs();

    void AddGraph(std::vector<double> const& xs, std::vector<double> const& ys, std::string const& name = "");

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetXAxis(std::string const& title, Range<double> const& range = Range<double>());

    void SetYAxis(std::string const& title, Range<double> const& range = Range<double>());

    void AddLine(double x_value, std::string const& title = "");

private:

    void Draw();

    Range<double> RangeY();

    Range<double> RangeX();

    void AddGraphs();

    TMultiGraph multi_graph_;

    Legend legend_;

    std::vector<TGraph> graphs_;

    std::vector<std::pair<TLine, std::string>> lines_;

    std::vector<std::pair<std::vector<double>, std::vector<double>>> datas_;

    Rectangle<double> range_;

};

}
