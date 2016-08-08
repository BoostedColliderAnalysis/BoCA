#include "include/analysis/NewPair.hh"
#include "include/tagger/EventNewPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::NewPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::ResonanceTagger>();
    Run<toppartner::NewPartnerHadronicTagger>();
    Run<toppartner::NewPartnerLeptonicTagger>();
    Run<toppartner::NewPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
    Run<toppartner::EventNewPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
