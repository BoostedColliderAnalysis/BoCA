#include "AnalysisNeutral.hh"
#include "EventNeutralTagger.hh"

int main()
{
    analysis::heavyhiggs::AnalysisNeutral<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::JetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::heavyhiggs::SignatureNeutralTagger> signature_semi_analysis;
    signature_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisNeutral<analysis::heavyhiggs::EventNeutralTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();

}

