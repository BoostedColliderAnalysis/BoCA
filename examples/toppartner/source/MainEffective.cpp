#include "include/analysis/Effective.hh"
#include "include/tagger/EventEffective.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::Effective<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::Higgs>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::HiggsPair>(boca::Output::efficiency);
    Run<toppartner::tagger::TopPartnerHadronicNeutral>(boca::Output::efficiency);
    Run<toppartner::tagger::TopPartnerLeptonicNeutral>(boca::Output::efficiency);
//     Run<toppartner::tagger::TopPartnerHadronicCharged>();
//     Run<toppartner::tagger::TopPartnerLeptonicCharged>();
//     Run<toppartner::tagger::TopPartnerHadronic>();
//     Run<toppartner::tagger::TopPartnerLeptonic>();
    Run<toppartner::tagger::SignatureEffective>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::tagger::EventEffective>(boca::Output::significance);
}
