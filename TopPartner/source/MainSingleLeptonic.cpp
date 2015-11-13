#include "AnalysisTopPartnerSingleLeptonic.hh"
#include "EventSingleLeptonicTagger.hh"
#include "Debug.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    Info0;
    boca::naturalness::AnalysisSingleLeptonic<Tagger> analysis;
    boca::Run(analysis, output);
}

int main()
{
    Info0;
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::VetoTopPartnerHadronicTagger>();
    Run<boca::naturalness::SignatureSingleLeptonicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::EventSingleLeptonicTagger>(boca::Output::significance);
}
