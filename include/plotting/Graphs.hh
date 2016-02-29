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

    void AddGraph(std::vector<float> const& xs, std::vector<float> const& ys, std::string const& name = "");

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetXAxis(std::string const& title, Range<float> const& range = Range<float>());

    void SetYAxis(std::string const& title, Range<float> const& range = Range<float>());

    void AddLine(float x_value, std::string const& title = "");

private:

    void Draw();

    Range<double> RangeY();

    Range<double> RangeX();

    void AddGraphs();

    TMultiGraph multi_graph_;

    Legend legend_;

    std::vector<TGraph> graphs_;

    std::vector<std::pair<TLine, std::string>> lines_;

    std::vector<std::pair<std::vector<float>, std::vector<float>>> datas_;

    Rectangle<float> range_;

};

}
