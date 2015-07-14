#include "AnalysisTopPartner.hh"

#include "EventSingleTagger.hh"
#include "Predicate.hh"

int main()
{
    try {
        analysis::toppartner::Analysis<analysis::BottomTagger> bottom_analysis;
        bottom_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::HiggsTagger> higgs_analysis;
        higgs_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::WLeptonicTagger> w_leptonic_analysis;
        w_leptonic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::BosonTagger> boson_analysis;
        boson_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::TopHadronicTagger> top_hadronic_analysis;
        top_hadronic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::TopLeptonicTagger> top_leptonic_analysis;
        top_leptonic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
        top_partner_leptonic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::toppartner::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
        top_partner_hadronic_analysis.RunFullEfficiency();
        top_partner_hadronic_analysis.RunPlots();

        analysis::toppartner::Analysis<analysis::toppartner::TopPartnerPairTagger> top_partner_leptonic_pair_analysis;
        top_partner_leptonic_pair_analysis.RunFullEfficiency();
        top_partner_hadronic_analysis.RunPlots();

        analysis::toppartner::Analysis<analysis::toppartner::EventSingleTagger> event_analysis;
        event_analysis.RunFullSignificance();
        top_partner_hadronic_analysis.RunPlots();
    } catch (const char *message) {
        std::cout << message << std::endl;
    }
}

