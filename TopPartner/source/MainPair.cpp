#include "AnalysisTopPartnerPair.hh"
#include "EventPairTagger.hh"


int main()
{
    boca::toppartner::AnalysisPair<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    boca::toppartner::AnalysisPair<boca::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    boca::toppartner::AnalysisPair<boca::toppartner::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    boca::toppartner::AnalysisPair<boca::toppartner::TopPartnerPairTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    boca::toppartner::AnalysisPair<boca::toppartner::EventPairTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

