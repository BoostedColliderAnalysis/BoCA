#pragma once

#include "AnalysisTagger.hh"

namespace analysis
{

  namespace standardmodel
{
/**
 *
 * @brief Higgs tagger analysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisHiggs : public analysis::standardmodel::Analysis
{

public:

    AnalysisHiggs(Tagger &tagger);

protected:

  virtual std::string ClassName() const;

private:

    void SetFiles(const Tag tag);

     std::string ProjectName() const;


    int PassPreCut(Event &event);

};

}

}
