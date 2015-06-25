# include "AnalysisTopPartner.hh"

# include "EventTagger.hh"
# include "EventSingleTagger.hh"

int main()
{

    bool single = true;

    analysis::BottomTagger bottom_tagger;
    analysis::toppartner::Analysis bottom_analysis(bottom_tagger);
    bottom_analysis.RunFast();

    analysis::HiggsTagger higgs_tagger;
    analysis::toppartner::Analysis higgs_analysis(higgs_tagger);
    higgs_analysis.RunFast();

    analysis::WHadronicTagger w_hadronic_tagger;
    analysis::toppartner::Analysis w_hadronic_analysis(w_hadronic_tagger);
    w_hadronic_analysis.RunFast();

    analysis::WSemiTagger w_semi_tagger;
    analysis::toppartner::Analysis w_semi_analysis(w_semi_tagger);
    w_semi_analysis.RunFast();

    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::toppartner::Analysis top_hadronic_analysis(top_hadronic_tagger);
    top_hadronic_analysis.RunFast();

    analysis::TopSemiTagger top_semi_tagger;
    analysis::toppartner::Analysis top_semi_analysis(top_semi_tagger);
    top_semi_analysis.RunFast();

    analysis::ZHadronicTagger z_hadronic_tagger;
    analysis::toppartner::Analysis z_hadronic_analysis(z_hadronic_tagger);
    z_hadronic_analysis.RunFast();

    analysis::toppartner::TopPartnerSemiTagger top_partner_semi_tagger;
    analysis::toppartner::Analysis top_partner_semi_analysis(top_partner_semi_tagger);
    top_partner_semi_analysis.RunFast();

    if (single) {

        analysis::toppartner::TopPartnerHiggsPairTagger top_partner_higgs_pair_tagger;
        analysis::toppartner::Analysis top_partner_higgs_pair_analysis(top_partner_higgs_pair_tagger);
        top_partner_higgs_pair_analysis.RunFast();

        analysis::toppartner::SignatureSingleTagger signature_tagger;
        analysis::toppartner::Analysis signature_analysis(signature_tagger);
        signature_analysis.RunFast();

        analysis::toppartner::EventSingleTagger event_tagger;
        analysis::toppartner::Analysis event_analysis(event_tagger);
        event_analysis.RunFast();

    } else {

//         analysis::toppartner::TopPartnerHadronicTagger top_partner_hadronic_tagger;
//         analysis::toppartner::Analysis top_partner_hadronic_analysis(top_partner_hadronic_tagger);
//         top_partner_hadronic_analysis.RunFast();
//
//         analysis::toppartner::HiggsPairTagger higgs_pair_tagger;
//         analysis::toppartner::Analysis higgs_pair_analysis(higgs_pair_tagger);
//         higgs_pair_analysis.RunFast();
//
//         analysis::toppartner::TopPartnerPairTagger top_partner_pair_tagger;
//         analysis::toppartner::Analysis top_partner_pair_analysis(top_partner_pair_tagger);
//         top_partner_pair_analysis.RunFast();
//
//         analysis::toppartner::SignatureTagger signature_tagger;
//         analysis::toppartner::Analysis signature_analysis(signature_tagger);
//         signature_analysis.RunFast();
//
//         analysis::toppartner::EventTagger event_tagger;
//         analysis::toppartner::Analysis event_analysis(event_tagger);
//         event_analysis.RunFast();

    }

}

