#include "AnalysisTop.hh"
#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"

int main()
{
    boca::standardmodel::TopAnalysis<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    switch (bottom_analysis.TopDecay()) {
    case boca::Decay::hadronic : {
        boca::standardmodel::TopAnalysis<boca::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunFast();
        boca::standardmodel::TopAnalysis<boca::TopHadronicTagger> top_hadronic_analysis;
        top_hadronic_analysis.RunFullEfficiency();
        top_hadronic_analysis.RunPlots();
        break;
    }
    case boca::Decay::leptonic : {
        boca::standardmodel::TopAnalysis<boca::TopLeptonicTagger> top_leptonic_analysis;
        top_leptonic_analysis.RunFullEfficiency();
        break;
    }
    }
}

