#include "AnalysisFusion.hh"
#include "EventFusionTagger.hh"

int main()
{
    analysis::heavyhiggs::AnalysisFusion<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::WSemiTagger> w_semi_analysis;
    w_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::TopSemiTagger> tops_semi_analysis;
    tops_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisFusion<analysis::heavyhiggs::EventFusionTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();

}

