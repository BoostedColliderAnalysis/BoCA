#include "boca/AnalysisNewPartnerPair.hh"
#include "boca/EventNewPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisNewPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<boca::toppartner::ResonanceTagger>();
    Run<boca::toppartner::NewPartnerHadronicTagger>();
    Run<boca::toppartner::NewPartnerLeptonicTagger>();
    Run<boca::toppartner::NewPartnerPairTagger>(boca::Output::efficiency | boca::Output::plot);
    Run<boca::toppartner::EventNewPairTagger>(boca::Output::efficiency | boca::Output::plot);
}
