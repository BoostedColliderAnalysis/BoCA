#include "AnalysisTopPartnerSingle.hh"
#include "EventSingleTagger.hh"

int main()
{
    boca::toppartner::AnalysisSingle<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();
    bottom_analysis.RunPlots();

    boca::toppartner::AnalysisSingle<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    boca::toppartner::AnalysisSingle<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    boca::toppartner::AnalysisSingle<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    boca::toppartner::AnalysisSingle<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    boca::toppartner::AnalysisSingle<boca::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    boca::toppartner::AnalysisSingle<boca::toppartner::TopPartnerTopPairTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    boca::toppartner::AnalysisSingle<boca::toppartner::SignatureSingleTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    boca::toppartner::AnalysisSingle<boca::toppartner::EventSingleTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

