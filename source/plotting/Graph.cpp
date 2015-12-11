
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "THStack.h"
#include "TList.h"
#include "TMultiGraph.h"
#include "TH2.h"
#include "TH1.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TExec.h"
#include "TLatex.h"
#include "TNamed.h"

#include "physics/Math.hh"
#include "plotting/Graph.hh"
#include "plotting/Canvas.hh"
#include "plotting/Font.hh"
#include "plotting/Style.hh"
#include "plotting/Result.hh"
#include "plotting/Font.hh"
#include "plotting/Legend.hh"
#include "plotting/Graphs.hh"
#include "Debug.hh"

namespace boca
{

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec)
{
    Info0;
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (auto const & point : plot.points) histogram.Fill(point.x, point.y);
    histogram.SetContour(20);
    switch (color) {
    case kRed :
        exec.SetAction("boca::Color().Red();");
        break;
    case kBlue :
        exec.SetAction("boca::Color().Blue();");
        break;
    default:
        Error("unsupported color");
    }
    exec.Draw();
    CommonHist(histogram, plot, color);
    histogram.Draw(options.c_str());
}

void SetProfile(TH2& histogram, Plot const& signal, Plot const& background)
{
    Info0;
    float max = (*boost::range::max_element(signal.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    float min = (*boost::range::min_element(background.points, [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    for (auto const & point : signal.points) histogram.Fill(point.x, point.y, point.z);
    for (auto const & point : background.points) histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    CommonHist(histogram, signal, kRed);
    SetAxis(*histogram.GetZaxis(), "BDT");
//     histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void CommonHist(TH1& histogram, Plot const& plot, EColor color)
{
    Info0;
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
    SetAxis(*histogram.GetXaxis(), plot.nice_name_x.c_str());
    SetAxis(*histogram.GetYaxis(), plot.nice_name_y.c_str());
}


}
