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
class hanalysis::HReader : public HObject
{

public:

    /**
     * @brief Default constructor
     *
     */
    HReader();

    /**
     * @brief Constructor
     *
     */
    HReader(hanalysis::Tagger &tagger);

    void operator=(const hanalysis::HReader &) {
        Print(HError, "invalid assigmnent operator!!", "Dont end up here!!!", "Actually it still seems to work");
    }

    void SetMva(hanalysis::Tagger &tagger);

    void SimpleMVALoop();

    float Bdt() const;

    int GetBdt(HEvent &event) const {
      if(!tagger_) Print(HError,"what is wrong with the tagger?");
        return tagger_->GetBdt(event, reader_);
    }

private:

    Tagger *tagger_;

    TMVA::Reader reader_;

    TMVA::Reader &reader() {
        return reader_;
    }

    Tagger &tagger() const {
        return *tagger_;
    }

    void BookMva();

    void AddVariable();

    HInfoBranch InfoBranch(TFile &file, const std::string &tree_name) const;

    std::vector<int> BdtDistribution(ExRootTreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    HMvaResult BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    inline std::string ClassName() const {
        return "HReader";
    }

};
