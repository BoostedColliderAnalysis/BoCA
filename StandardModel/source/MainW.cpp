#include "AnalysisWTagger.hh"
#include "WHadronicTagger.hh"
#include "WSemiTagger.hh"

int main()
{
    analysis::standardmodel::AnalysisW<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    switch (bottom_analysis.WDecay()) {
    case analysis::standardmodel::Decay::hadronic : {
        analysis::standardmodel::AnalysisW<analysis::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunFullEfficiency();
        break;
    }
    case analysis::standardmodel::Decay::semi : {
        analysis::standardmodel::AnalysisW<analysis::WSemiTagger> w_semi_analysis;
        w_semi_analysis.RunFullEfficiency();
        break;
    }
    }
}

