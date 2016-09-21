#include "toppartner/analysis/SubDom.hh"
#include "toppartner/tagger/EventSubDom.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::SubDom<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::Higgs>();
    Run<standardmodel::tagger::Boson>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerHadronic>(boca::Output::efficiency);
    Run<toppartner::tagger::TopPartnerLeptonic>(boca::Output::efficiency);
//     Run<toppartner::tagger::SignatureSubDom>(boca::Output::significance);
//     Run<standardmodel::tagger::Global>(boca::Output::significance);
//     Run<toppartner::tagger::EventSubDom>(boca::Output::significance);
}
