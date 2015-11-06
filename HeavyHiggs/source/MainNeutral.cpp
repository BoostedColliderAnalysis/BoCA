#include "AnalysisNeutral.hh"
#include "EventNeutralTagger.hh"

int main()
{
  boca::heavyhiggs::AnalysisNeutral<boca::standardmodel::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::JetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::standardmodel::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::standardmodel::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::standardmodel::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::standardmodel::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::heavyhiggs::SignatureNeutralTagger> signature_semi_analysis;
    signature_semi_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutral<boca::heavyhiggs::EventNeutralTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();
}

