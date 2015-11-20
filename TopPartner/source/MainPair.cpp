#include "EventPairTagger.hh"
#include "AnalysisTopPartnerPair.hh"


int main()
{
    analysis::toppartner::AnalysisPair<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    analysis::toppartner::AnalysisPair<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    analysis::toppartner::AnalysisPair<analysis::toppartner::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    analysis::toppartner::AnalysisPair<analysis::toppartner::TopPartnerPairTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    analysis::toppartner::AnalysisPair<analysis::toppartner::EventPairTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

