#include "AnalysisTopPartnerSingleLeptonic.hh"
#include "EventSingleLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisSingleLeptonic<Tagger> analysis;
    boca::Run(analysis, output);
}

int main()
{
    Run<boca::BottomTagger>();
    Run<boca::HiggsTagger>();
    Run<boca::BosonTagger>();
    Run<boca::WHadronicTagger>();
    Run<boca::TopHadronicTagger>();
    Run<boca::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::TopPartnerHadronicTagger>();
    Run<boca::naturalness::SignatureSingleLeptonicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::EventSingleLeptonicTagger>(boca::Output::significance);
}
