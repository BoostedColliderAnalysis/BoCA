# pragma once

#include "Rtypes.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraph.h"

#include "Flag.hh"

class TH1F;
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

enum class Orientation
{
    center = 1 << 0,
    left = 1 << 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4
};

template<>
struct Flag<Orientation> {
  static const bool enable = true;
};

TH1F Histogram(const Result& result, Point& max, Point const& min, int index);

void AddHistogram(THStack& stack, TH1& histogram, TLegend& legend);

TLegend Legend(Point const& min, float width, float height, std::string const& title = "");

TLegend Legend(Orientation orientation, std::vector<std::string> const& entries, std::string const& title = "");

TLine Line(float bin, float y_min, float y_max, int index);

void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, std::vector<std::string> const& names, int index);

void SetMultiGraph(TMultiGraph& multi_graph, Point const& min, Point const& max);

TGraph Graph(Results const& results, std::vector<float> const& values, std::string const& title);

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec);

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background);

void CommonHist(TH1& histogram, Plot const& plot, EColor color);



TGraph CutGraph(CutResults const& results, std::vector<float> const& values, std::string const& title);
TLine CutLine(float bin, float y_min, float y_max, int index);

}
