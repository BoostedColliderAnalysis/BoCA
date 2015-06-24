# pragma once

# include "AnalysisTagger.hh"

namespace analysis
{

  namespace standardmodel
{

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

    enum Decay {kLeptonic, kHadronic, kSemi};

    Decay TopDecay() const;

protected:

    virtual std::string ClassName() const;

private:

    void SetFiles(const Object::Tag tag);

    std::string ProjectName() const;


    int PassPreCut(Event &event);

};

}

}
