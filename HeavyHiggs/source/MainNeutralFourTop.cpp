#include "AnalysisNeutralFourTop.hh"
#include "EventNeutralFourTopTagger.hh"

int main()
{
    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::JetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunNormal();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::WSemiTagger> w_semi_analysis;
    w_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunNormal();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::heavyhiggs::SignatureNeutralTagger> signature_semi_analysis;
    signature_semi_analysis.RunNormal();

    analysis::heavyhiggs::AnalysisNeutralFourTop<analysis::heavyhiggs::EventNeutralFourTopTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();

}

