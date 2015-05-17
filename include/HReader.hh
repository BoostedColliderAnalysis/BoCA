# pragma once

# include "Tagger.hh"
# include "Event.hh"

class HMvaResult : analysis::Object
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
class analysis::HReader : public Object
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
    HReader(analysis::Tagger &tagger);

    void operator=(const analysis::HReader &) {
        Print(kError, "invalid assigmnent operator!!", "Dont end up here!!!", "Actually it still seems to work");
    }

    void SetMva(analysis::Tagger &tagger);

    void SimpleMVALoop();

    float Bdt() const;

    int GetBdt(Event &event) const {
      if(!tagger_) Print(kError,"what is wrong with the tagger?");
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

    InfoBranch info_branch(TFile &file, const std::string &tree_name) const;

    std::vector<int> BdtDistribution(ExRootTreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    HMvaResult BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    inline std::string ClassName() const {
        return "HReader";
    }

};
