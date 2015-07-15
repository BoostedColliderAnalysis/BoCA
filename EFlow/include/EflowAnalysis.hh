# pragma once

# include "Analysis.hh"
# include "delphes/Hadrons.hh"
# include "FourVector.hh"


namespace analysis{

namespace eflow {
/**
 *
 * @brief EFlow ananlysis
 *
 * @author Ying-Ying Li
 *
 */

enum class Decay
{
    leptonic, hadronic, semi
};

class EflowAnalysis : public analysis::Analysis
{

public:

    EflowAnalysis(Tagger &tagger);
    
    void AnalysisMain();
    
    TLegend Legend(float x_min, float y_max, float width, float height, const std::string &name = "");
    
    Jets SetJetType(const Tag tag, Event &event);
    void JetTypeName(const Tag tag);

//     std::vector<TH1F> RunJetNum(Event &event, const Tag tag, std::vector<TH1F> &histograms);
    
    private:

    void SetFiles(const Tag tag);
    
    Strings nice_names_;

    
        

};

}

}