#include "AnalysisTopPartnerSingleLeptonic.hh"
#include "EventSingleLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisSingleLeptonic<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::naturalness::VetoTopPartnerHadronicTagger>();
    Run<boca::naturalness::SignatureSingleLeptonicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::EventSingleLeptonicTagger>(boca::Output::significance);
}
