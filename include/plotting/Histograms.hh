#pragma once

#include <vector>

#include "TH1F.h"
#include "THStack.h"
#include "TLine.h"

#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

namespace boca
{

class Histograms : public Canvas
{

public:

    Histograms(std::string const& path, std::string const& name, bool has_title = false);

    ~Histograms();

    void AddHistogram(std::vector<float> const& values, std::string const& name, Limits& limits_x, Limits & limits_y);

    void SetLegend(Orientation orientation, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Limits const& limits = Limits());

    void SetYAxis(std::string const& title, Limits const& limits = Limits());

    void AddLine(float x_value);

private:

    Limits LimitsY();

    void AddHistograms();

    void SetCorners(Point const& min, float width, float height);

    THStack stack_;

    Legend legend_;

    std::vector<TH1F> histograms_;

    std::vector<TLine> lines_;

};

}
