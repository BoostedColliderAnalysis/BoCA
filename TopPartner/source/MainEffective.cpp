#include "AnalysisTopPartnerEffective.hh"
#include "EventEffectiveTagger.hh"

int main()
{
        analysis::toppartner::AnalysisEffective<analysis::BottomTagger> bottom_analysis;
        bottom_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::HiggsTagger> higgs_analysis;
        higgs_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::BosonTagger> boson_analysis;
        boson_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::toppartner::HiggsPairTagger> higgs_pair_analysis;
        higgs_pair_analysis.RunFullEfficiency();
        higgs_pair_analysis.RunPlots();

        analysis::toppartner::AnalysisEffective<analysis::TopHadronicTagger> top_hadronic_analysis;
        top_hadronic_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::TopLeptonicTagger> top_leptonic_analysis;
        top_leptonic_analysis.RunNormal();

        analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
        top_partner_leptonic_analysis.RunFullEfficiency();

        analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
        top_partner_hadronic_analysis.RunFullEfficiency();
        top_partner_hadronic_analysis.RunPlots();

        analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerPairTagger> top_partner_pair_analysis;
        top_partner_pair_analysis.RunFullEfficiency();
        top_partner_pair_analysis.RunPlots();

        analysis::toppartner::AnalysisEffective<analysis::toppartner::EventEffectiveTagger> event_analysis;
        event_analysis.RunFullSignificance();
        event_analysis.RunPlots();
}

