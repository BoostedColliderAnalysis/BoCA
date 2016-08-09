#include "include/analysis/Pair.hh"
#include "include/tagger/EventPair.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::Pair<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerHadronicNeutral>();
    Run<toppartner::tagger::TopPartnerLeptonicNeutral>();
    Run<toppartner::tagger::TopPartnerPair>(boca::Output::significance);
    Run<boca::tagger::Global>(boca::Output::significance);
    Run<toppartner::tagger::EventPair>(boca::Output::significance);
}
