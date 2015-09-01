#include "AnalysisHiggs.hh"
#include "HiggsTagger.hh"

int main()
{
    boca::standardmodel::AnalysisHiggs<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::standardmodel::AnalysisHiggs<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunFullEfficiency();
    higgs_analysis.RunPlots();
}

