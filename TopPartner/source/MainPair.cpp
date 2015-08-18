#include "AnalysisTopPartnerPair.hh"
#include "EventPairTagger.hh"


int main()
{
    boca::naturalness::AnalysisPair<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    boca::naturalness::AnalysisPair<boca::naturalness::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    boca::naturalness::AnalysisPair<boca::naturalness::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    boca::naturalness::AnalysisPair<boca::naturalness::TopPartnerPairTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    boca::naturalness::AnalysisPair<boca::naturalness::EventPairTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

