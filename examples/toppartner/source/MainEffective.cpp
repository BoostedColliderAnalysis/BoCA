#include "toppartner/analysis/Effective.hh"
#include "toppartner/tagger/EventEffective.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    toppartner::analysis::Effective<Tagger_> analysis;
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
    Run<toppartner::tagger::HiggsPair>();
    Run<toppartner::tagger::TopPartnerHadronic>();
    Run<toppartner::tagger::TopPartnerLeptonic>();
    Run<standardmodel::tagger::Global>(boca::Output::significance);
    Run<toppartner::tagger::SignatureEffective>(boca::Output::significance);
    Run<toppartner::tagger::EventEffective>(boca::Output::significance);
}
