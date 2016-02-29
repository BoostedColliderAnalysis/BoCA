#include "AnalysisTopPartnerEffective.hh"
#include "EventEffectiveTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisEffective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::HiggsPairTagger>();
    Run<boca::naturalness::TopPartnerHadronicNeutralTagger>();
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>();
//     Run<boca::naturalness::TopPartnerHadronicChargedTagger>();
//     Run<boca::naturalness::TopPartnerLeptonicChargedTagger>();
//     Run<boca::naturalness::TopPartnerHadronicTagger>();
//     Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::SignatureEffectiveTagger>(boca::Output::significance | boca::Output::plot);
    Run<boca::EventTagger>(boca::Output::significance | boca::Output::plot);
    Run<boca::naturalness::EventEffectiveTagger>(boca::Output::significance | boca::Output::plot);
}
