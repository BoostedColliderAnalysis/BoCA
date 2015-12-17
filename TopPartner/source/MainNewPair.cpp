#include "AnalysisNewPartnerPair.hh"
#include "EventNewPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisNewPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::ResonanceTagger>();
    Run<boca::naturalness::NewPartnerHadronicTagger>();
    Run<boca::naturalness::NewPartnerLeptonicTagger>();
    Run<boca::naturalness::NewPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
    Run<boca::naturalness::EventNewPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
