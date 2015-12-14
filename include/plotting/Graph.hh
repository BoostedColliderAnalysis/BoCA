# pragma once

#include "Rtypes.h"

class TH1;
class TH2;
class TExec;

namespace boca
{

class Plot;

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec);

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background);

void CommonHist(TH1& histogram, Plot const& plot, EColor color);

}
