#include "AnalysisTopPartnerSingle.hh"
#include "EventSingleTagger.hh"

int main()
{
    try {

        analysis::toppartner::Analysis<analysis::BottomTagger> bottom_analysis;
        bottom_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::HiggsTagger> higgs_analysis;
        higgs_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::WLeptonicTagger> w_leptonic_analysis;
        w_leptonic_analysis.RunNormal();

//         analysis::toppartner::Analysis<analysis::BosonTagger> boson_analysis;
//         boson_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::TopHadronicTagger> top_hadronic_analysis;
        top_hadronic_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::TopLeptonicTagger> top_leptonic_analysis;
        top_leptonic_analysis.RunNormal();

        analysis::toppartner::Analysis<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
        top_partner_leptonic_analysis.RunFullEfficiency();

        analysis::toppartner::Analysis<analysis::toppartner::TopPartnerTopPairTagger> top_partner_hadronic_analysis;
        top_partner_hadronic_analysis.RunFullEfficiency();
        top_partner_hadronic_analysis.RunPlots();

        analysis::toppartner::Analysis<analysis::toppartner::SignatureSingleTagger> top_partner_pair_analysis;
        top_partner_pair_analysis.RunFullEfficiency();
        top_partner_pair_analysis.RunPlots();

        analysis::toppartner::Analysis<analysis::toppartner::EventSingleTagger> event_analysis;
        event_analysis.RunFullSignificance();
        event_analysis.RunPlots();
    } catch (const char* message) {
        std::cout << message << std::endl;
    }
}

