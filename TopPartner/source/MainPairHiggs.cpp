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
    Run<boca::toppartner::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::SignatureEffectiveTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventEffectiveTagger>(boca::Output::significance);
}
