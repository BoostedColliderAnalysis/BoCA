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

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec);

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background);

void CommonHist(TH1& histogram, Plot const& plot, EColor color);

}
