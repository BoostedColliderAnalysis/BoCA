# pragma once

#include "Rtypes.h"
#include "TH1F.h"
#include "TLine.h"
#include "TGraph.h"

#include "Flag.hh"

class TH1;
class TLegend;
class TMultiGraph;
class TH2;
class THStack;
class TLine;
class TGraph;
class TExec;

namespace boca
{

class Point;
class Plot;
class Result;
class Results;
class CutResults;
class Legend;
class Limits;

TH1F Histogram(const Result& result, Point& max, Point const& min, int index);

void AddHistogram(THStack& stack, TH1& histogram, Legend& legend);

TLine Line(float bin, float y_min, float y_max, int index);

TLine Line(float bin, Limits const& limits_y, int index);

void AddGraph(TGraph& graph, TMultiGraph& multi_graph, Legend& legend, std::vector<std::string> const& names, int index);

void SetMultiGraph(TMultiGraph& multi_graph, Point const& min, Point const& max);

TGraph Graph(Results const& results, std::vector<float> const& values, std::string const& title);

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec);

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background);

void CommonHist(TH1& histogram, Plot const& plot, EColor color);

TGraph CutGraph(CutResults const& results, std::vector<float> const& values, std::string const& title);
TLine CutLine(float bin, float y_min, float y_max, int index);

}
