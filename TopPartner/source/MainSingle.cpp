#include "AnalysisTopPartnerSingle.hh"
#include "EventSingleTagger.hh"

int main()
{
    analysis::toppartner::AnalysisSingle<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();
    bottom_analysis.RunPlots();

    analysis::toppartner::AnalysisSingle<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    analysis::toppartner::AnalysisSingle<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisSingle<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisSingle<analysis::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    analysis::toppartner::AnalysisSingle<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    analysis::toppartner::AnalysisSingle<analysis::toppartner::TopPartnerTopPairTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    analysis::toppartner::AnalysisSingle<analysis::toppartner::SignatureSingleTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    analysis::toppartner::AnalysisSingle<analysis::toppartner::EventSingleTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

