#pragma once

#include "Tagger.hh"
#include "Event.hh"
#include "Branches.hh"
#include "TGraph.h"
#include "TLegend.h"

namespace analysis
{

class Result : Object
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
    int event_sum() {
//         return info_branch.EventNumber;
      return event_sum_;
    }
    void set_event_sum(const int event_sum) {
        event_sum_ = event_sum;
    }
private:
    int event_sum_;
};

struct Results {

public:

    std::vector<Result> signal;
    std::vector<Result> background;
};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Reader : public Object
{

public:

    /**
     * @brief Default constructor
     *
     */
    Reader();

    /**
     * @brief Constructor
     *
     */
    Reader(Tagger &tagger);

    void SetTagger(Tagger &tagger);

    void TaggingEfficiency();

    void OptimalSignificance();

    float Bdt() const;

    TLegend Legend(float x_min, float y_max, float width, float height, const std::string &name = "");

    Results ExportFile() const;

    std::vector<Result> Export(TFile &export_file, const std::string &file_name, const analysis::Strings &treename) const;

    void PlotMultiGraph(const analysis::Results &results);

    void PlotHistograms(const analysis::Results &results);

    int GetBdt(Event &event, PreCuts &pre_cuts) const {
        if (!tagger_) Print(Severity::error, "what is wrong with the tagger?");
        return tagger().GetBdt(event, pre_cuts, reader_);
    }

    template <typename Tagger, typename Input>
    auto Multiplets(Input &input) const {
        PreCuts pre_cuts;
        return static_cast<Tagger &>(tagger()).Multiplets(input, pre_cuts, reader_);
    }

    template <typename Tagger, typename Input1, typename Input2>
    auto Multiplets(Input1 &input_1, Input2 &input_2) {
        return static_cast<Tagger &>(tagger()).Multiplets(input_1, input_2, reader_);
    }

    template <typename Tagger, typename Input>
    auto Multiplet(Input &input) {
        return static_cast<Tagger &>(tagger()).Multiplet(input, reader_);
    }

    template <typename Tagger, typename Input1, typename Input2>
    auto Multiplet(Input1 &input_1, Input2 &input_2) {
        return static_cast<Tagger &>(tagger()).Multiplet(input_1, input_2, reader_);
    }

    template <typename Tagger, typename Input>
    auto SubMultiplet(Input &input, const int number) {
        return static_cast<Tagger &>(tagger()).SubMultiplet(input, reader_, number);
    }

    template <typename Tagger, typename Input>
    auto SubMultiplet(Input &input) {
        return static_cast<Tagger &>(tagger()).SubMultiplet(input, reader_);
    }

    TMVA::Reader &reader() {
        return reader_;
    }

    Tagger &tagger() const {
        return *tagger_;
    }

private:

    Tagger *tagger_;

    TMVA::Reader reader_;

    void BookMva();

    void AddVariable();

    analysis::InfoBranch InfoBranch(TFile &file, const std::string &tree_name) const;

    Result BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    Result BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    std::string ClassName() const {
        return "Reader";
    }

    int ColorCode(const int number) const;

    std::string ExportName() const{
      return tagger().analysis_name() + "/" + tagger().analysis_name() + "-" + tagger().name();
    }

};

}
