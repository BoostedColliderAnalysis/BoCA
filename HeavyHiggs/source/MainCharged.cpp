#include "AnalysisCharged.hh"
#include "EventChargedTagger.hh"

int main()
{
    analysis::heavyhiggs::AnalysisCharged<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::WSemiTagger> w_semi_analysis;
    w_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::TopSemiTagger> tops_semi_analysis;
    tops_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::ChargedHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::TripletJetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::SignatureChargedTagger> signature_semi_analysis;
    signature_semi_analysis.RunFast();

    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::EventChargedTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();
}
