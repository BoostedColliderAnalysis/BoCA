# pragma once

# include "AnalysisTagger.hh"

namespace analysis
{

  namespace standardmodel
{
/**
 *
 * @brief W tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisZ : public analysis::standardmodel::Analysis
{

public:


    AnalysisZ(Tagger &tagger);

protected:

    virtual  std::string ClassName() const {
        return "AnalysisZ";
    }

private:

    void SetFiles(const Tag tag);

     std::string ProjectName() const;

    int PassPreCut(Event &event);

};

}

}
