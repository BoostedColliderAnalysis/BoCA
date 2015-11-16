#include "AnalysisTopPartnerPair.hh"
#include "EventPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
  boca::naturalness::AnalysisPair<Tagger> analysis;
  boca::Run(analysis, output);
}

int main()
{
  Run<boca::standardmodel::BottomTagger>();
  Run<boca::standardmodel::WHadronicTagger>();
  Run<boca::standardmodel::BosonTagger>();
  Run<boca::standardmodel::TopHadronicTagger>();
  Run<boca::standardmodel::TopLeptonicTagger>();
  Run<boca::naturalness::TopPartnerHadronicTagger>();
  Run<boca::naturalness::TopPartnerLeptonicTagger>();
  Run<boca::naturalness::TopPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
  Run<boca::naturalness::EventPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
