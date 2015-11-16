#include "AnalysisFusion.hh"
#include "EventFusionTagger.hh"

int main()
{
    boca::heavyhiggs::AnalysisFusion<boca::standardmodel::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::standardmodel::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::standardmodel::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::standardmodel::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::standardmodel::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::heavyhiggs::EventFusionTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();
}

