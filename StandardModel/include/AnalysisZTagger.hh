#pragma once

#include "AnalysisTagger.hh"

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

private:

    void SetFiles(const Tag tag);

     std::string ProjectName() const;

    int PassPreCut(const Event &event);

};

}

}
