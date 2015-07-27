#include "AnalysisCharged.hh"
#include "EventChargedTagger.hh"

int main()
{
    analysis::heavyhiggs::AnalysisCharged<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::ChargedHiggsSemiTagger> heavy_higgs_leptonic_analysis;
    heavy_higgs_leptonic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::TripletJetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::SignatureChargedTagger> signature_leptonic_analysis;
    signature_leptonic_analysis.RunFast();
    analysis::heavyhiggs::AnalysisCharged<analysis::heavyhiggs::EventChargedTagger> event_leptonic_analysis;
    event_leptonic_analysis.RunFullSignificance();
}
