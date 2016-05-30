#include "boca/AnalysisNewPartnerPair.hh"
#include "boca/EventNewPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisNewPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::toppartner::ResonanceTagger>();
    Run<boca::toppartner::NewPartnerHadronicTagger>();
    Run<boca::toppartner::NewPartnerLeptonicTagger>();
    Run<boca::toppartner::NewPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
    Run<boca::toppartner::EventNewPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
