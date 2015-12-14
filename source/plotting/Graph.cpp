
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
    for (auto const & point : plot.Data()) histogram.Fill(point.X(), point.Y());
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
    float max = (*boost::range::max_element(signal.Data(), [](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Z() < b.Z();
    })).Z();
    float min = (*boost::range::min_element(background.Data(), [](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Z() < b.Z();
    })).Z();
    for (auto const & point : signal.Data()) histogram.Fill(point.X(), point.Y(), point.Z());
    for (auto const & point : background.Data()) histogram.Fill(point.X(), point.Y(), point.Z());
    Color().Heat();
    CommonHist(histogram, signal, kRed);
    SetTitle(*histogram.GetZaxis(), "BDT");
//     histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void CommonHist(TH1& histogram, Plot const& plot, EColor color)
{
    Info0;
}


}
