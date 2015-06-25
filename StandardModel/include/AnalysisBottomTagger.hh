# pragma once

# include "AnalysisTagger.hh"

namespace analysis
{

  namespace standardmodel
{

/**
 *
 * @brief  Bottom Tagger Analysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisBottom : public analysis::standardmodel::Analysis
{

public:

    AnalysisBottom(Tagger &tagger);

protected:

    virtual  std::string ClassName() const {
        return "AnalysisBottom";
    }

private:

    enum ProductionChannel {DYP, VBF, Associated};

    ProductionChannel production_channel() const;

    std::string ProjectName() const;

    std::string ProductionChannelName(const ProductionChannel production_channel) const;

    void SetFiles(const Object::Tag Tag);

    int PassPreCut(Event &event);

};

}

}
