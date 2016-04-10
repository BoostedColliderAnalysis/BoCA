#include "AnalysisTopPartnerPair.hh"
#include "EventPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisPair<Tagger> analysis;
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
    Run<boca::naturalness::TopPartnerHadronicNeutralTagger>();
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>();
    Run<boca::naturalness::TopPartnerPairTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::naturalness::EventPairTagger>(boca::Output::significance);
}
