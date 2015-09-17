#include "AnalysisTopPartnerEffective.hh"
#include "EventEffectiveTagger.hh"

int main()
{

    boca::naturalness::AnalysisEffective<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::naturalness::HiggsPairTagger> higgs_pair_analysis;
    higgs_pair_analysis.RunFullEfficiency();
    higgs_pair_analysis.RunPlots();

    boca::naturalness::AnalysisEffective<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    boca::naturalness::AnalysisEffective<boca::naturalness::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    boca::naturalness::AnalysisEffective<boca::naturalness::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    boca::naturalness::AnalysisEffective<boca::naturalness::TopPartnerPairTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    boca::naturalness::AnalysisEffective<boca::naturalness::SignatureEffectiveTagger> signature_analysis;
    signature_analysis.RunFullEfficiency();
    signature_analysis.RunPlots();

    boca::naturalness::AnalysisEffective<boca::naturalness::EventEffectiveTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

