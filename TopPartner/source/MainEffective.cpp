#include "AnalysisTopPartnerEffective.hh"
#include "EventEffectiveTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
  boca::naturalness::AnalysisEffective<Tagger> analysis;
  boca::Run(analysis, output);
}

int main()
{
  Run<boca::BottomTagger>();
  Run<boca::WHadronicTagger>();
  Run<boca::HiggsTagger>();
  Run<boca::BosonTagger>();
  Run<boca::TopHadronicTagger>();
  Run<boca::TopLeptonicTagger>();
  Run<boca::naturalness::HiggsPairTagger>();
  Run<boca::naturalness::TopPartnerHadronicTagger>();
  Run<boca::naturalness::TopPartnerLeptonicTagger>();
  Run<boca::naturalness::TopPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
  Run<boca::naturalness::SignatureEffectiveTagger>(boca::Output::efficiency | boca::Output::plot);
  Run<boca::naturalness::EventEffectiveTagger>(boca::Output::significance | boca::Output::plot);
}
