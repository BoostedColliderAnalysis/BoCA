#include "boca/AnalysisTopPartnerPair.hh"
#include "boca/EventPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::toppartner::TopPartnerHadronicNeutralTagger>();
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>();
    Run<boca::toppartner::TopPartnerPairTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventPairTagger>(boca::Output::significance);
}
