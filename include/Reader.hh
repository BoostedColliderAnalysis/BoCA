# pragma once

# include "Tagger.hh"
# include "HEvent.hh"

class HMvaResult : hanalysis::HObject
{

public:

    HMvaResult();
    std::vector<int> CutIntegral(const std::vector< int > &bins) const;

    int Steps;
    std::vector<float> Events;
    std::vector<float> Efficiency;
    std::vector<int> AnalysisEventNumber;
    std::vector<float> Bdt;
    int TotalEventNumber;
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
        Print(HError, "invalid assigmnent operator!!", "Dont end up here!!!", "Actually it still seems to work");
    }

    void set_tagger(hanalysis::Tagger &tagger);

    void OptimalSignificance();

    float Bdt() const;

    int GetBdt(HEvent &event) const {
        if (!tagger_) Print(HError, "what is wrong with the tagger?");
        return tagger_->GetBdt(event, reader_);
    }

//     template <typename Multiplet>
//     std::vector<Multiplet>
//     auto GetMultiplets(HEvent &event) {
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

    HInfoBranch InfoBranch(TFile &file, const std::string &tree_name) const;

    std::vector<int> BdtDistribution(ExRootTreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    HMvaResult BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    inline std::string ClassName() const {
        return "Reader";
    }

};
}
