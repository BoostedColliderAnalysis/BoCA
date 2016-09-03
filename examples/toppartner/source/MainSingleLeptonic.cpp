#include "toppartner/analysis/SingleLeptonic.hh"
#include "toppartner/tagger/EventSingleLeptonic.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::SingleLeptonic<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::Higgs>();
    Run<standardmodel::tagger::Boson>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerLeptonicNeutral>(boca::Output::efficiency);
    Run<toppartner::tagger::VetoTopPartnerHadronic>(boca::Output::efficiency);
    Run<toppartner::tagger::SignatureSingleLeptonic>(boca::Output::significance);
    Run<boca::tagger::Global>(boca::Output::significance);
    Run<toppartner::tagger::EventSingleLeptonic>(boca::Output::significance);
}
