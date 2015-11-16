#include "AnalysisNeutralFourTop.hh"
#include "EventNeutralFourTopTagger.hh"

int main()
{
  boca::heavyhiggs::AnalysisNeutralFourTop<boca::standardmodel::BottomTagger> bottom_analysis;

    bottom_analysis.RunNormal();


    boca::heavyhiggs::AnalysisNeutralFourTop<boca::JetPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunNormal();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::standardmodel::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::standardmodel::WLeptonicTagger> w_semi_analysis;
    w_semi_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::standardmodel::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::standardmodel::TopLeptonicTagger> tops_leptonic_analysis;
    tops_leptonic_analysis.RunFast();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::heavyhiggs::HeavyHiggsSemiTagger> heavy_higgs_semi_analysis;
    heavy_higgs_semi_analysis.RunNormal();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::heavyhiggs::SignatureNeutralTagger> signature_semi_analysis;
    signature_semi_analysis.RunNormal();
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::heavyhiggs::EventNeutralFourTopTagger> event_semi_analysis;
    event_semi_analysis.RunFullSignificance();
}

