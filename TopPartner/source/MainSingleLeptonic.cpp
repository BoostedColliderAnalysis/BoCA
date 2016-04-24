#include "boca/AnalysisTopPartnerSingleLeptonic.hh"
#include "boca/EventSingleLeptonicTagger.hh"

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
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::naturalness::VetoTopPartnerHadronicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::SignatureSingleLeptonicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::naturalness::EventSingleLeptonicTagger>(boca::Output::significance);
}
