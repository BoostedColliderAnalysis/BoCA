#include "AnalysisBottomTagger.hh"
#include "BottomTagger.hh"

int main()
{
    analysis::BottomTagger bottom_tagger;
    analysis::standardmodel::AnalysisBottom bottom_analysis(bottom_tagger);
    bottom_analysis.RunFull();
}
