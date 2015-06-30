#pragma once

#include "AnalysisTagger.hh"

namespace analysis
{

namespace standardmodel
{

enum class Decay
{
    leptonic, hadronic, semi
};

/**
 *
 * @brief Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
class TopAnalysis : public analysis::standardmodel::Analysis
{

public:

    TopAnalysis(Tagger &tagger);

    Decay TopDecay() const;

private:

    void SetFiles(const Tag tag);

    std::string ProjectName() const;

    int PassPreCut(Event &event);

    std::string DecayName(const Decay decay) const;

};

}

}
