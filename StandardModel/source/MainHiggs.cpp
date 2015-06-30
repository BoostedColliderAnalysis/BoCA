#include "AnalysisHiggsTagger.hh"
#include "HiggsTagger.hh"

int main()
{
    analysis::BottomTagger bottom_tagger;
    analysis::standardmodel::AnalysisHiggs bottom_analysis(bottom_tagger);
    bottom_analysis.RunFast();

    analysis::HiggsTagger higgs_tagger;
    analysis::standardmodel::AnalysisHiggs higgs_analysis(higgs_tagger);
    higgs_analysis.RunFull();
}

