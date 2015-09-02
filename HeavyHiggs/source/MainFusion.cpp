#include "AnalysisFusion.hh"
#include "EventFusionTagger.hh"

int main()
{
    boca::heavyhiggs::AnalysisFusion<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();
    boca::heavyhiggs::AnalysisFusion<boca::heavyhiggs::EventFusionTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();
}

