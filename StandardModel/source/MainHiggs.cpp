#include "AnalysisHiggs.hh"
#include "HiggsTagger.hh"

int main()
{
    analysis::standardmodel::AnalysisHiggs<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::standardmodel::AnalysisHiggs<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunFullEfficiency();
}

