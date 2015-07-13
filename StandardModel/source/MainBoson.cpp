#include "AnalysisBoson.hh"
#include "BosonTagger.hh"

int main()
{
    analysis::standardmodel::AnalysisBoson<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::standardmodel::AnalysisBoson<analysis::BosonTagger> boson_analysis;
    boson_analysis.RunFullEfficiency();
}

