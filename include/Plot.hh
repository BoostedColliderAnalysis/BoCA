#pragma once

#include "Tagger.hh"
#include "TLegend.h"
#include "Branches.hh"

namespace analysis
{

class Result
{

public:

    Result();
    std::vector<int> CutIntegral() const;

    int steps;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<int> analysis_event_number;
    std::vector<float> bdt;
    std::vector<int> bins;
    InfoBranch info_branch;
    int event_sum() const;
    void set_event_sum(const int event_sum);
private:
    int event_sum_;
};

struct Results {

public:

  Results();

    std::vector<Result> signal;
    std::vector<Result> background;
    std::vector<float> significances;
    std::vector<float> x_values;
    int best_bin = 0;

    void Significances();

    void BestBin();



};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Plot
{

public:

    /**
     * @brief Default constructor
     *
     */
//     Plot();

    /**
     * @brief Constructor
     *
     */
    Plot(Tagger &tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

private:

    float Bdt() const;

    TLegend Legend(float x_min, float y_max, float width, float height, const std::string &name = "") const;

    Results ExportFile() const;

    std::vector<Result> Export(TFile &export_file, const std::string &file_name, const analysis::Strings &treename) const;

    void PlotMultiGraph(const analysis::Results &results) const;

    std::string PlotHistograms(const analysis::Results &results) const;

    Tagger &tagger() const {
        return *tagger_;
    }

    Tagger *tagger_;

    analysis::InfoBranch InfoBranch(TFile &file, const std::string &tree_name) const;

    Result BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    Result BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    std::string PlotEfficiencyGraph(const analysis::Results &results, const std::vector< float > &x_values, const int best_bin) const;

    std::string PlotSignificanceGraph(const Results &results, const std::vector<float> &x_values, const std::vector<float> &significances, const int best_bin) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    int ColorCode(const int number) const;

    std::string ExportName() const;

};

}
