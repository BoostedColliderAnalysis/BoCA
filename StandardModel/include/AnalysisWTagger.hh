# pragma once

# include "AnalysisTagger.hh"

namespace analysis
{

namespace standardmodel
{

enum class Decay {semi, hadronic};

/**
 *
 * @brief HAnalysis subclass defining the W Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisW : public analysis::standardmodel::Analysis
{

public:

    AnalysisW(Tagger &tagger);

    Decay WDecay() const;

protected:

    virtual  std::string ClassName() const {
        return "AnalysisW";
    }

private:

    void SetFiles(const Tag tag);

    std::string ProjectName() const;

    int PassPreCut(Event &event);

};

}

}
