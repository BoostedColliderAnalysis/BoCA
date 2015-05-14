# pragma once

# include "Tagger.hh"
# include "Event.hh"

class HMvaResult : hanalysis::HObject
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
namespace hanalysis{
class Reader : public HObject
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
    Reader(hanalysis::Tagger &tagger);

    void operator=(const hanalysis::Reader &) {
        Print(kError, "invalid assigmnent operator!!", "Dont end up here!!!", "Actually it still seems to work");
    }

    void set_tagger(hanalysis::Tagger &tagger);

    void OptimalSignificance();

    float Bdt() const;

    int GetBdt(Event &event, PreCuts &pre_cuts) const {
        if (!tagger_) Print(kError, "what is wrong with the tagger?");
        return tagger_->GetBdt(event, pre_cuts, reader_);
    }

//     template <typename Multiplet>
//     std::vector<Multiplet>
//     auto GetMultiplets(Event &event) {
//         return tagger_->GetMultiplets(event, reader_);
//     }

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

    std::vector<int> BdtDistribution(ExRootTreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    HMvaResult BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    inline std::string ClassName() const {
        return "Reader";
    }

};
}
