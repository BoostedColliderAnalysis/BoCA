#include "AnalysisZ.hh"
#include "ZHadronicTagger.hh"

int main()
{
    analysis::standardmodel::AnalysisZ<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    analysis::standardmodel::AnalysisZ<analysis::ZHadronicTagger> z_hadronic_analysis;
    z_hadronic_analysis.RunFullEfficiency();
}

