#include "toppartner/analysis/Pair.hh"
#include "toppartner/tagger/EventPair.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::Pair<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::Boson>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerHadronic>();
    Run<toppartner::tagger::TopPartnerLeptonic>();
    Run<toppartner::tagger::TopPartnerPair>(boca::Output::significance);
    Run<standardmodel::tagger::Global>(boca::Output::significance);
    Run<toppartner::tagger::EventPair>(boca::Output::significance);
}
