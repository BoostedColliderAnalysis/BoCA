# pragma once

# include "Tagger.hh"
# include "Event.hh"
# include "Branches.hh"

namespace analysis
{

class HMvaResult : Object
{

public:

    HMvaResult();
    std::vector<int> CutIntegral(const std::vector< int > &bins) const;

    int Steps;
    std::vector<float> events;
    std::vector<float> Efficiency;
    std::vector<int> AnalysiseventNumber;
    std::vector<float> Bdt;
    int TotaleventNumber;
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

    void set_tagger(Tagger &tagger);

    void OptimalSignificance();

    float Bdt() const;

    int GetBdt(Event &event, PreCuts &pre_cuts) const {
        if (!tagger_) Print(kError, "what is wrong with the tagger?");
        return tagger().GetBdt(event, pre_cuts, reader_);
    }

    template <typename Tagger, typename Input>
    auto Multiplets(Input &input) {
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

    InfoBranch info_branch(TFile &file, const std::string &tree_name) const;

    std::vector<int> BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    HMvaResult BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    inline std::string ClassName() const {
        return "Reader";
    }

};
}
