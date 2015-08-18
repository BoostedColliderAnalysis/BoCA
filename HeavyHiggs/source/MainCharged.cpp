#include "AnalysisCharged.hh"
#include "EventChargedTagger.hh"

int main()
{
    boca::heavyhiggs::AnalysisCharged<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::heavyhiggs::ChargedHiggsSemiTagger> heavy_higgs_leptonic_analysis;
    heavy_higgs_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::TripletJetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::heavyhiggs::SignatureChargedTagger> signature_leptonic_analysis;
    signature_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisCharged<boca::heavyhiggs::EventChargedTagger> event_leptonic_analysis;
    event_leptonic_analysis.RunFullSignificance();
}
