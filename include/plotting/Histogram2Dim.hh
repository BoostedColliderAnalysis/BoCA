#pragma once

#include <vector>

#include "TH2F.h"
#include "TExec.h"

#include "plotting/Canvas.hh"
#include "plotting/Legend.hh"

class Plot;
// class EColor;

namespace boca
{

class Histogram2Dim : public Canvas
{

public:

    Histogram2Dim(std::string const& path, std::string const& name, bool show_title = false);

    ~Histogram2Dim();

    void SetLegend(Orientation orientation, std::string const& title = "");

    void SetLegend(Vector2<float> const& point, float width, float height, std::string const& title = "");

    void Draw();

    void SetXAxis(std::string const& title, Limits<float> const& limits = Limits<float>());

    void SetYAxis(std::string const& title, Limits<float> const& limits = Limits<float>());

    void AddHistogram(std::string const& name, int bins,  Vector2<float> const& min, Vector2<float> const& max, std::vector<Vector3<float>> const& points, EColor color);

    boca::Legend & Legend(){
      return legend_;
    }

private:

    void SetExec(EColor color);

    boca::Legend legend_;

    std::vector<TH2F> histograms_;

    std::vector<TExec> execs_;


};

}
