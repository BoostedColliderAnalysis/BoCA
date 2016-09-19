/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLine.h"

#include "boca/plotting/Legend.hh"
#include "boca/plotting/Canvas.hh"

namespace boca
{

class Graphs : public Canvas
{

public:

    Graphs(std::string const& path, std::string const& name, bool show_title = false);

    ~Graphs();

    void AddGraph(std::vector<double> const& xs, std::vector<double> const& ys, latex::String const& name = latex::String());

    void SetLegend(Orientation orientation, latex::String const& title = latex::String());

    void SetXAxis(const boca::latex::String& title, boca::Range<double> const& range = Range<double>());

    void SetYAxis(const boca::latex::String& title, boca::Range<double> const& range = Range<double>());

    void AddLine(double x_value, latex::String const& title = latex::String());

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

