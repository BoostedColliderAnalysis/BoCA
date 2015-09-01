#include "AnalysisZ.hh"
#include "ZHadronicTagger.hh"

int main()
{
    boca::standardmodel::AnalysisZ<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::standardmodel::AnalysisZ<boca::ZHadronicTagger> z_hadronic_analysis;
    z_hadronic_analysis.RunFullEfficiency();
}

