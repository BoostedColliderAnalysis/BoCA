#include "boca/AnalysisTopPartnerEffective.hh"
#include "boca/EventEffectiveTagger.hh"

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
    Run<boca::naturalness::HiggsPairTagger>(boca::Output::efficiency);
    Run<boca::naturalness::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
//     Run<boca::naturalness::TopPartnerHadronicChargedTagger>();
//     Run<boca::naturalness::TopPartnerLeptonicChargedTagger>();
//     Run<boca::naturalness::TopPartnerHadronicTagger>();
//     Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::SignatureEffectiveTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::naturalness::EventEffectiveTagger>(boca::Output::significance);
}
