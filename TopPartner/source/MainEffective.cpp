#include "boca/AnalysisTopPartnerEffective.hh"
#include "boca/EventEffectiveTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisEffective<Tagger> analysis;
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
    Run<boca::toppartner::HiggsPairTagger>(boca::Output::efficiency);
    Run<boca::toppartner::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
//     Run<boca::toppartner::TopPartnerHadronicChargedTagger>();
//     Run<boca::toppartner::TopPartnerLeptonicChargedTagger>();
//     Run<boca::toppartner::TopPartnerHadronicTagger>();
//     Run<boca::toppartner::TopPartnerLeptonicTagger>();
    Run<boca::toppartner::SignatureEffectiveTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventEffectiveTagger>(boca::Output::significance);
}
