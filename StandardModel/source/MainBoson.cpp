#include "AnalysisBoson.hh"
#include "BosonTagger.hh"

int main()
{
    boca::standardmodel::AnalysisBoson<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::standardmodel::AnalysisBoson<boca::BosonTagger> boson_analysis;
    boson_analysis.RunFullEfficiency();
}

