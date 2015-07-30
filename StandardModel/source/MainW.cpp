#include "AnalysisW.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"

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
    case analysis::standardmodel::Decay::leptonic : {
        analysis::standardmodel::AnalysisW<analysis::WLeptonicTagger> w_leptonic_analysis;
        w_leptonic_analysis.RunFullEfficiency();
        break;
    }
    }
}

