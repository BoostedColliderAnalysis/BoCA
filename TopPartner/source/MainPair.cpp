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
  Run<boca::BottomTagger>();
  Run<boca::WHadronicTagger>();
  Run<boca::BosonTagger>();
  Run<boca::TopHadronicTagger>();
  Run<boca::TopLeptonicTagger>();
  Run<boca::naturalness::TopPartnerHadronicTagger>();
  Run<boca::naturalness::TopPartnerLeptonicTagger>();
  Run<boca::naturalness::TopPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
  Run<boca::naturalness::EventPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
