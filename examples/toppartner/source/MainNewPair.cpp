#include "include/analysis/NewPair.hh"
#include "include/tagger/EventNewPair.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::NewPair<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::Resonance>();
    Run<toppartner::tagger::NewPartnerHadronic>();
    Run<toppartner::tagger::NewPartnerLeptonic>();
    Run<toppartner::tagger::NewPartnerPair>(boca::Output::efficiency | boca::Output::plot);
    Run<toppartner::tagger::EventNewPair>(boca::Output::efficiency | boca::Output::plot);
}
