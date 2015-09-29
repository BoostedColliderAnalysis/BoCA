#include "AnalysisTopPartnerSingle.hh"
#include "EventSingleTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::naturalness::AnalysisSingle<Tagger> analysis;
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
    Run<boca::naturalness::TopPartnerHadronicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::SignatureSingleTagger>(boca::Output::efficiency | boca::Output::plot);
    Run<boca::naturalness::EventSingleTagger>(boca::Output::significance);
}
