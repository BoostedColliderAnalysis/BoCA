#include "AnalysisZTagger.hh"
#include "ZHadronicTagger.hh"

int main()
{
    analysis::BottomTagger bottom_tagger;
    analysis::standardmodel::AnalysisZ bottom_analysis(bottom_tagger);
    bottom_analysis.RunFast();

    analysis::ZHadronicTagger z_hadronic_tagger;
    analysis::standardmodel::AnalysisZ z_hadronic_analysis(z_hadronic_tagger);
    z_hadronic_analysis.RunFull();
}

