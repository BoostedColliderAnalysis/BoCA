#include "include/analysis/SingleLeptonic.hh"
#include "include/tagger/EventSingleLeptonic.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::SingleLeptonic<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::Higgs>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerLeptonicNeutral>(boca::Output::efficiency);
    Run<toppartner::tagger::VetoTopPartnerHadronic>(boca::Output::efficiency);
    Run<toppartner::tagger::SignatureSingleLeptonic>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::tagger::EventSingleLeptonic>(boca::Output::significance);
}
