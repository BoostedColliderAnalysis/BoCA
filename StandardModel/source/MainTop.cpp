#include "AnalysisTop.hh"
#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"

int main()
{
    analysis::standardmodel::TopAnalysis<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    switch (bottom_analysis.TopDecay()) {
    case analysis::standardmodel::Decay::hadronic : {
        analysis::standardmodel::TopAnalysis<analysis::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunFast();

        analysis::standardmodel::TopAnalysis<analysis::TopHadronicTagger> top_hadronic_analysis;
        top_hadronic_analysis.RunFullEfficiency();
        top_hadronic_analysis.RunPlots();
        break;
    }
    case analysis::standardmodel::Decay::leptonic : {
        analysis::standardmodel::TopAnalysis<analysis::TopLeptonicTagger> top_leptonic_analysis;
        top_leptonic_analysis.RunFullEfficiency();
        break;
    }
    }
}

